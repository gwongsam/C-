#pragma once
#include <atomic>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "function_wrapper.hpp"
#include "join_threads.hpp"
#include "threads.hpp"
#include "threadsafe_queue.hpp"

class thread_pool {
 private:
  std::atomic_bool done;
  threadsafe_queue<function_wrapper> work_queue;
  std::vector<std::thread> threads;
  join_threads joiner;
  void worker_thread() {
    while (!done) {
      function_wrapper task;
      if (work_queue.try_pop(task)) {
        task();
      } else {
        std::this_thread::yield();
      }
    }
  }

 public:
  thread_pool() : done(false), joiner(threads) {
    unsigned const thread_count = std::thread::hardware_concurrency();
    try {
      for (unsigned i = 0; i < thread_count; ++i) {
        threads.push_back(std::thread(&thread_pool::worker_thread, this));
      }
    } catch (...) {
      done = true;
      throw;
    }
  }

  ~thread_pool() { done = true; }

  // template <typename FunctionType>
  // void submit(FunctionType f) {
  //   work_queue.push(std::function<void()>(f));
  // }

  template <typename FunctionType>
  std::future<typename std::result_of<FunctionType()>::type> submit(
      FunctionType f) {
    typedef typename std::result_of<FunctionType()>::type result_type;

    std::packaged_task<result_type()> task(std::move(f));
    std::future<result_type> res(task.get_future());
    work_queue.push(std::move(task));
    return res;
  }
};
