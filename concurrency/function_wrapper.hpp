#pragma once
#include <memory>
#include <thread>
#include <future>
#include <iostream>
#include <exception>
#include "threadsafe_queue.hpp"
#include "threads.hpp"

class FunctionWrapper
{
    struct ImplBase
    {
        virtual void call() = 0;
        virtual ~ImplBase() {}
    };
    std::unique_ptr<ImplBase> impl_;
    template <typename F>
    struct impl_type : ImplBase
    {
        F f_;
        impl_type(F &&f) : f_(std::move(f)) {}
        void call() { f_(); }
    };

public:
    template <typename F>
    FunctionWrapper(F &&f) : impl_(new impl_type<F>(std::move(f))) {}
    FunctionWrapper() = default;
    FunctionWrapper(FunctionWrapper &&other) : impl_(std::move(other.impl_)) {}
    // FunctionWrapper(const FunctionWrapper &) = delete;
    // FunctionWrapper(FunctionWrapper &) = delete;
    FunctionWrapper &operator=(const FunctionWrapper &) = delete;
    FunctionWrapper &operator=(FunctionWrapper &&other)
    {
        impl_ = std::move(other.impl_);
        return *this;
    }
    void operator()() { impl_->call(); }
};

class thread_pool
{
    std::atomic_bool done_;
    threadsafe_queue<FunctionWrapper> work_queue_;
    std::vector<std::thread> threads_;
    JoinThreads joiner_;
    void worker_thread()
    {
        while (!done_)
        {
            FunctionWrapper task;
            if (work_queue_.try_pop(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }

public:
    thread_pool() :done_(false), joiner_(threads_)
    {
        unsigned const thread_count = std::thread::hardware_concurrency();
        try
        {
            for (unsigned i = 0; i < thread_count; ++i)
            {
                threads_.emplace_back(&thread_pool::work_queue_, this);
            }
        }
        catch(const std::exception& e)
        {
            done_ = true;
            std::cerr << e.what() << '\n';
        }
    }
    ~thread_pool() { done_ = true; }
    template <typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type>
    Submit(FunctionType f)
    {
        typedef typename std::result_of<FunctionType()>::type result_type;
        std::packaged_task<result_type> task(std::move(f));
        std::future<result_type> res(task.get_future());
        work_queue_.push(std::move(task));
        return res;
    }
};