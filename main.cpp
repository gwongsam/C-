#include <iostream>
#include <atomic>
#include <list>
#include <string>
#include <future>
#include <coroutine>
#include <thread>
#include <stdexcept>
#include <compare>
#include <iostream>
#include <bitset>
#include "concurrency/threadsafe_stack.hpp"
#include "concurrency/threadsafe_queue.hpp"
#include "concurrency/lock_free_stack.hpp"
#include "concurrency/thread_pool.hpp"
//#include "concurrency/function_wrapper.hpp"
#include "algorithms/searching.hpp"
#include "algorithms/sorting.hpp"
#include "algorithms/structure.hpp"
//#include "interface/iconvertible.hpp"
#include "public/public.hpp"
#include "algorithms/graph.hpp"
#include "algorithms/heap_priority_queue.hpp"
#include "algorithms/string.hpp"
#include "algorithms/digraph.hpp"

using namespace std;
using namespace graph;
using namespace interface;
using namespace algo;

auto SwitchToNewThread(std::jthread &out)
{
    struct Awaitable
    {
        std::jthread *out_ptr;
        bool await_ready() { return false; }
        void await_suspend(std::coroutine_handle<> h)
        {
            std::jthread &out = *out_ptr;
            if (out.joinable())
                throw std::runtime_error("Output jthread parameter not empty");
            out = std::jthread([h]
                               { h.resume(); });
            std::cout << "New Thread ID: " << out.get_id() << '\n';
        }
        void await_resume() {}
    };
    return Awaitable{&out};
}

struct Task
{
    struct promise_type
    {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

Task ResumingOnNewThread(std::jthread &out)
{
    std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << "\n";
    co_await SwitchToNewThread(out);
    std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << "\n";
}

int main()
{
    // Digraph digraph;
    // digraph.AddEdge(1, 2);
    // digraph.AddEdge(2, 3);
    // digraph.AddEdge(1, 3);
    // // digraph.AddEdge(3, 1);
    // string str = digraph.ToString();
    // cout << str;
    // DirectedDFS dfs(digraph, 2);
    // cout << dfs.Marked(1) << endl;
    // auto arr = Public::IO::ReadLines("key_indexed.txt");
    // vector<pair<size_t, string>> students;
    // for (auto &item : arr)
    // {
    //     auto vec = Public::SplitDelim(item, " ");
    //     if (vec.size() < 2)
    //     {
    //         continue;
    //     }
    //     pair<size_t, string> p = make_pair(stoi(vec[1]), vec[0]);
    //     students.emplace_back(p);
    // }
    // for (auto &item : students)
    // {
    //     cout << item.first << " " << item.second << endl;
    // }
    // KeyIndexed ki;
    // ki.Counting(students, 4);
    // for (auto &item : students)
    // {
    //     cout << item.second << " " << item.first << endl;
    // }
    std::vector<std::string> arr = Public::IO::ReadLines("licence_plate.txt");
    LSD lsd;
    lsd.Sort(arr, 7);
    // for (auto &item : arr)
    // {
    //     cout << item << endl;
    // }
    return 0;
}
