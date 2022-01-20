#pragma once
#include <vector>
#include <thread>

class JoinThreads
{
private:
    std::vector<std::thread>& threads_;
public:
    explicit JoinThreads(std::vector<std::thread>& threads) : threads_(threads)
    {

    }
    ~JoinThreads()
    {
        for (unsigned long i = 0; i < threads_.size(); ++i)
        {
            if (threads_[i].joinable())
            {
                threads_[i].join();
            }
        }
    }
};