#pragma once
#include <vector>
#include <atomic>
#include <thread>
#include <functional>
#include <iostream>
#include "threadsafe_queue.hpp"
#include "threads.hpp"

class ThreadPool
{
private:
    std::atomic_bool done_;
    threadsafe_queue<std::function<void()>> work_queue_;
    std::vector<std::thread> threads_;
    JoinThreads joiner_;
    void WorkerThread()
    {
        while (!done_)
        {
            std::function<void()> task;
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
    ThreadPool() : done_(false), joiner_(threads_)
    {
        unsigned const thread_count = std::thread::hardware_concurrency();
        std::cout << "hardware_concurrency::" << thread_count << std::endl;
        try
        {
            for (unsigned i = 0; i < thread_count; ++i)
            {
                threads_.emplace_back(std::thread(&ThreadPool::WorkerThread, this));
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            done_ = true;
            throw;
        }
    }
    ~ThreadPool()
    {
        done_  = true;
    }
    template<typename FunctionType>
    void Submit(FunctionType f)
    {
        std::cout << "Submit" << std::endl;
        work_queue_.push(std::function<void()>(f));
        std::cout << "Submit exit" << std::endl;
    }
};