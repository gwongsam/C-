#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace algo
{
    class KeyIndexed
    {
    public:
        void Counting(std::vector<std::pair<size_t, std::string>> &arr, size_t r)
        {
            size_t len = arr.size();
            std::pair<size_t, std::string> aux[len];
            size_t count[r + 1]{0};

            // Compute frequency counts.
            for (size_t i = 0; i < len; i++)
            {
                count[arr[i].first + 1]++;
            }
            // Transform counts to indices.
            for (size_t i = 0; i < r; i++)
            {
                count[i + 1] += count[i];
            }
            // Distribute the records.
            for (size_t i = 0; i < len; i++)
            {
                aux[count[arr[i].first]++] = arr[i];
            }
            // Copy back.
            for (size_t i = 0; i < len; i++)
            {
                arr[i] = aux[i];
            }
        }
    };

    class LSD
    {
    public:
        void Sort(std::vector<std::string> &arr, size_t w)
        {
            for (auto &item : arr)
            {
                std::cout << item << std::endl;
            }
            return;
            if (arr.empty())
            {
                return;
            }
            size_t n = arr.size();
            size_t r = 256;
            auto aux = new std::string[n];
            for (size_t d = w - 1; d >= 0; d--)
            {
                size_t count[r + 1]{0};
                // Compute frequency counts.
                for (size_t i = 0; i < n; i++)
                {
                    count[(size_t)arr[i][d] + 1]++;
                }
                // Transform counts to indices.
                for (size_t i = 0; i < r; i++)
                {
                    count[i + 1] += count[i];
                }
                // Distribute.
                for (size_t i = 0; i < n; i++)
                {
                    aux[count[(size_t)arr[i][d]]++] = arr[i];
                }
                // Copy back.
                for (size_t i = 0; i < n; i++)
                {
                    arr[i] = aux[i];
                }
            }

            delete[] aux;
        }
    };

    class String
    {
    public:
        String() {}
        String(const char *args)
        {
            std::string s = args;
            *this = s;
        }
        char operator[](unsigned long long index)
        {
            if (index > size - 1)
            {
                return ' ';
            }
            return a_[index];
        }
        String &operator=(std::string s)
        {
            delete a_;
            a_ = new char[](s.size());
            for (size_t i = 0; i < s.size(); ++i)
            {
                a_[i] = s[i];
            }
            return *this;
        }
        unsigned long long size = 0;

    private:
        char *a_ = nullptr;
    };

    class Alphabet
    {
    public:
        Alphabet(String s)
        {
        }

        char ToChar(int index)
        {
            return ' ';
        }

        int ToIndex(char c)
        {
            return 0;
        }

        bool Contains(char c)
        {
            return false;
        }

        int Radix()
        {
            return 0;
        }

        String ToChars(int indices[])
        {
            return "";
        }
    };
}