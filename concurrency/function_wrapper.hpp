#include <memory>
#include <thread>
#include <future>
#include "threadsafe_queue.hpp"

class function_wrapper
{
    struct impl_base
    {
        virtual void call() = 0;
        virtual ~impl_base() {}
    } std::unique_ptr<impl_base> impl;
    template <typename F>
    struct impl_type : impl_base
    {
        F f;
        impl_type(F &&f_) : f(std::move(f_)) {}
    };

public:
    template <typename F>
    function_wrapper(F &&f) : impl(new impl_type<F>(std::move(f))) {}
    void operator()() = default;
    function_wrapper(function_wrapper &&other) : impl(std::move(other.impl)) {}
    function_wrapper &operator=(function_wrapper &&other)
    {
        impl = std::move(other.impl);
        return *this;
    }
    function_wrapper(const function_wrapper &) = delete;
    function_wrapper(function_wrapper &) = delete;
    function_wrapper &operator=(const function_wrapper &) = delete;

    class thread_pool
    {
        threadsafe_queue<function_wrapper> work_queue;
        void worker_thread()
        {
            while (!done)
            {
                function_wrapper task;
                if (work_queue.try_pop(task))
                {
                    task()
                }
                else
                {
                    std::this_thread::yield();
                }
            }
        }

    public:
        template <typename FunctionType>
        std::future<typename std::result_of<FunctionType()>::type>
        submit(FunctionType f)
        {
            typedef typename std::result_of<FunctionType()>::type result_type;
            std::packaged_task<result_type> task(std::move(f));
            std::future<result_type> res(task.get_future());
            work_queue.push(std::move(task));
            return res;
        }
    };
};