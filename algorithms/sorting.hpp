#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>

template <typename Comparable>
class Sorting
{
private:
public:
    virtual int Sort(std::vector<Comparable> &arr) = 0;
    virtual int Show(std::vector<Comparable> &arr)
    {
        for (auto &item : arr)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        return 0;
    }

    virtual bool IsSorted(std::vector<Comparable> &arr)
    {
        for (size_t i = 0; i < arr.size() - 2; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                return false;
            }
        }

        return true;
    }
};

template <typename Comparable>
class Bubble : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        size_t count = arr.size();
        for (size_t i = 0; i < count; i++)
        {
            for (size_t j = i; j < count; j++)
            {
                if (arr[i] > arr[j])
                {
                    std::swap(arr[i], arr[j]);
                }
            }
        }

        return 0;
    }
};

template <typename Comparable>
class Bucket : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        std::vector<Comparable> buckets[10];

        for (size_t i = 0; i < arr.size(); i++)
        {
            size_t idx = arr[i] / 100000;
            buckets[idx].emplace_back(arr[i]);
        }

        for (size_t i = 0; i < 10; i++)
        {
            Bubble<Comparable> quick;
            quick.Sort(buckets[i]);
        }

        arr.clear();
        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 0; j < buckets[i].size(); j++)
            {
                arr.emplace_back(buckets[i][j]);
            }
        }

        return 0;
    }
};

template <typename Comparable>
class Selection : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        size_t smallest = 0;
        for (size_t i = 0; i < arr.size(); i++)
        {
            smallest = i;
            for (size_t j = i + 1; j < arr.size(); j++)
            {
                if (arr[j] < arr[smallest])
                {
                    smallest = j;
                }
            }
            if (smallest != i)
            {
                std::swap(arr[i], arr[smallest]);
            }
        }

        return 0;
    }
};

template <typename Comparable>
class Insertion : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        for (size_t i = 1; i < arr.size(); i++)
        {
            for (size_t j = i; 0 < j && arr[j] < arr[j - 1]; j--)
            {
                std::swap(arr[j], arr[j - 1]);
            }
        }

        return 0;
    }
};

template <typename Comparable>
class Shellsort : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        size_t n = arr.size();
        size_t h = 1;
        while (h < n / 3)
        {
            h = 3 * h + 1;
        }
        while (h >= 1)
        {
            for (size_t i = 1; i < arr.size(); i++)
            {
                for (size_t j = i; h <= j && arr[j] < arr[j - h]; j -= h)
                {
                    std::swap(arr[j], arr[j - h]);
                }
            }
            h = h / 3;
        }

        return 0;
    }
};

template <typename Comparable>
class Mergesort : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        aux.resize(arr.size());
        Sort(arr, 0, arr.size() - 1);
        aux.clear();
        aux.shrink_to_fit();
        return 0;
    }

private:
    int Sort(std::vector<Comparable> &arr, size_t low, size_t high)
    {
        if (high <= low)
        {
            return 0;
        }
        size_t mid = low + (high - low) / 2;
        Sort(arr, low, mid);
        Sort(arr, mid + 1, high);
        Merge(arr, low, mid, high);
        return 0;
    }
    int Merge(std::vector<Comparable> &arr, size_t low, size_t mid, size_t high)
    {
        int i = low;
        int j = mid + 1;
        for (size_t k = low; k <= high; k++)
        {
            aux[k] = arr[k];
        }
        for (size_t k = low; k <= high; k++)
        {
            if (i > mid)
            {
                arr[k] = aux[j++];
            }
            else if (j > high)
            {
                arr[k] = aux[i++];
            }
            else if (aux[i] > aux[j])
            {
                arr[k] = aux[j++];
            }
            else
            {
                arr[k] = aux[i++];
            }
        }

        return 0;
    }

private:
    std::vector<Comparable> aux;
};

template <typename Comparable>
class Quicksort : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        Sort(arr, 0, arr.size() - 1);
        return 0;
    }

private:
    int Sort(std::vector<Comparable> &arr, size_t low, size_t high)
    {
        if (high <= low)
        {
            return 0;
        }
        size_t pivot = Partition(arr, low, high);
        Sort(arr, low, pivot - 1);
        Sort(arr, pivot + 1, high);

        return 0;
    }
    size_t Partition(std::vector<Comparable> &arr, size_t low, size_t high)
    {
        size_t i = low;
        size_t j = high + 1;
        Comparable pivot = arr[low];
        while (true)
        {
            while (arr[++i] < pivot)
            {
                if (i == high)
                {
                    break;
                }
            }
            while (pivot < arr[--j])
            {
                if (j == low)
                {
                    break;
                }
            }
            if (i >= j)
            {
                break;
            }
            std::swap(arr[i], arr[j]);
        }
        std::swap(arr[low], arr[j]);

        return j;
    }
};

template <typename Comparable>
class Heapsort : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr)
    {
        size_t n = arr.size();
        for (size_t i = n / 2; i >= 1; i--)
        {
            Sink(arr, i, n);
        }
        while (n > 1)
        {
            std::swap(arr[1], arr[n--]);
            Sink(arr, 1, n);
        }

        return 0;
    }

private:
    void Sink(std::vector<Comparable> &nums, size_t start, size_t end)
    {
    }
};

template <typename Comparable>
class Counting : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        std::vector<std::pair<unsigned long, Comparable>> counter;
        counter.resize(100000, std::make_pair(0, arr[0]));
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i] < 100000)
            {
                counter[arr[i]].first++;
                counter[arr[i]].second = arr[i];
            }
            else
            {
                return 1;
            }
        }
        arr.clear();
        for (size_t i = 0; i < counter.size(); i++)
        {
            for (size_t j = 0; j < counter[i].first; j++)
            {
                arr.emplace_back(counter[i].second);
            }
        }

        return 0;
    }
};

template <typename Comparable>
class RadixSort : public RadixSort<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr)
    {
        return 0;
    }
};