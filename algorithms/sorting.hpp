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
    // virtual int Sort(std::vector<std::shared_ptr<Comparable>> &arr) = 0;
    // virtual int Show(std::vector<std::shared_ptr<Comparable>> &arr)
    // {
    //     for (auto item : arr)
    //     {
    //         std::cout << *item << " ";
    //     }
    //     std::cout << std::endl;
    //     return 0;
    // }
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
class Bucket : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        std::vector<std::pair<unsigned long, Comparable>> bucket;
        bucket.resize(100, std::make_pair(0, arr[0]));
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i] < 100)
            {
                bucket[i].first++;
                bucket[i].second = arr[i];
            }
        }
        arr.clear();
        for (size_t i = 0; i < bucket.size(); i++)
        {
            for (size_t j = 0; j < bucket[i].first; j++)
            {
                arr.emplace_back(bucket[i].second);
            }
        }

        return 0;
    }
    // int Sort(std::vector<std::shared_ptr<Comparable>> &arr) override
    // {
    //     std::vector<unsigned long> bucket;
    //     bucket.resize(arr.size(), 0);
    //     for (size_t i = 0; i < arr.size(); i++)
    //     {
    //         if (*arr[i] < 100)
    //         {
    //             bucket[*arr[i]]++;
    //         }
    //     }
    //     arr.clear();
    //     for (size_t i = 0; i < bucket.size(); i++)
    //     {
    //         for (size_t j = 0; j < bucket[i]; j++)
    //         {
    //             arr.emplace_back(std::make_shared<int>(i));
    //         }
    //     }

    //     return 0;
    // }
};

template <typename Comparable>
class Selection : public Sorting<Comparable>
{
public:
    int Sort(std::vector<Comparable> &arr) override
    {
        int smallest = 0;
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
    // int Sort(std::vector<std::shared_ptr<Comparable>> &arr) override
    // {
    //     return 0;
    // }
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
    // int Sort(std::vector<std::shared_ptr<Comparable>> &arr) override
    // {
    //     return 0;
    // }
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
    // int Sort(std::vector<std::shared_ptr<Comparable>> &arr) override
    // {
    //     return 0;
    // }
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
    // int Sort(std::vector<Comparable> &arr) override
    // {
    //     size_t N = arr.size();
    //     aux.resize(N);
    //     for (size_t sz = 0; sz < N; sz = sz + sz)
    //     {
    //         for (size_t low = 0; low < N - sz; low += sz + sz)
    //         {
    //             Merge(arr, low, low + sz - 1, low + sz + sz - 1 < N - 1 ? low + sz + sz - 1 : N - 1);
    //         }
    //     }
        
    //     return 0;
    // }
    // int Sort(std::vector<std::shared_ptr<Comparable>> &arr) override
    // {
    //     return 0;
    // }

private:
    int Sort(std::vector<Comparable>& arr, size_t low, size_t high)
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
    // int Sort(std::vector<std::shared_ptr<Comparable>> &arr) override
    // {
    //     return 0;
    // }

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
        // size_t N = arr.size();
        // for (size_t k = 0; k < 1; k--)
        // {
        //     Sink(arr, k, N);
        // }
        // while (N > 1)
        // {
        //     std::swap(arr[1], arr[N--]);
        //     Sink(arr, 1, N);
        // }
        
        return 0;
    }
};
