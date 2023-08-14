
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

struct Task {
  int priority;  // Define the priority (higher value means higher priority in
                 // this example)
  std::function<void()> func;  // The task function

  // Constructor
  Task(int p, std::function<void()> f) : priority(p), func(f) {}
};

struct CompareTask {
  bool operator()(const Task& t1, const Task& t2) {
    return t1.priority <
           t2.priority;  // Note: It's '<' to make std::priority_queue a
                         // max-heap based on priority
  }
};

class ThreadPool {
 private:
  std::vector<std::thread> workers;
  std::priority_queue<Task, std::vector<Task>, CompareTask> tasks;

  std::mutex tasksMutex;
  std::condition_variable condition;
  std::atomic<bool> stop;

 public:
  ThreadPool(size_t threads) : stop(false) {
    for (size_t i = 0; i < threads; ++i) {
      workers.emplace_back([this] {
        while (true) {
          std::function<void()> task;

          {
            std::unique_lock<std::mutex> lock(this->tasksMutex);
            this->condition.wait(lock, [this] {
              return this->stop.load() || !this->tasks.empty();
            });

            if (this->stop.load() && this->tasks.empty()) return;

            task = std::move(this->tasks.top().func);
            this->tasks.pop();
          }

          task();
        }
      });
    }
  }

  void enqueue(int priority, std::function<void()> task) {
    {
      std::unique_lock<std::mutex> lock(tasksMutex);
      tasks.emplace(priority, task);
    }
    condition.notify_one();
  }

  ~ThreadPool() {
    stop.store(true);
    condition.notify_all();

    for (std::thread& worker : workers) worker.join();
  }
};