#pragma once
#include <vector>
#include <string>
#include "../interface/iconvertible.hpp"

template <typename Comparable>
class MaxPQ : interface::IConvertible
{
public:
    MaxPQ() { priority_queue_.emplace_back(Comparable()); }

    MaxPQ(size_t max_n)
    {
        priority_queue_.resize(max_n);
        priority_queue_.emplace_back(Comparable());
    }

    size_t Size() { return priority_queue_.size() - 1; }

    void Insert(Comparable v)
    {
        priority_queue_.emplace_back(v);
        Swin(Size());
    }

    Comparable DeleteMax()
    {
        Comparable max = priority_queue_[1];
        std::swap(priority_queue_[1], priority_queue_.back());
        priority_queue_.pop_back();
        Sink(1);
        return max;
    }

    std::string ToString() override
    {
        std::string str;
        for (auto &item : priority_queue_)
        {
            str += std::to_string(item) + " ";
        }
        return std::move(str);
    }

private:
    void Swin(size_t child)
    {
        while (1 < child && priority_queue_[child / 2] < priority_queue_[child])
        {
            std::swap(priority_queue_[child / 2], priority_queue_[child]);
            child /= 2;
        }
    }

    void Sink(size_t parent)
    {
        while (2 * parent <= Size())
        {
            size_t lchild = 2 * parent;
            if (lchild < Size() && priority_queue_[lchild] < priority_queue_[lchild + 1])
            {
                lchild++;
            }
            if (priority_queue_[parent] > priority_queue_[lchild])
            {
                break;
            }
            std::swap(priority_queue_[parent], priority_queue_[lchild]);
            parent = lchild;
        }
    }

private:
    std::vector<Comparable> priority_queue_;
};