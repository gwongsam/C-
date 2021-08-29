#include <mutex>
#include <atomic>

class SpinlockMutex
{
public:
    SpinlockMutex() :flag(ATOMIC_FLAG_INIT){}
    void Lock()
    {
        while (flag.test_and_set(std::memory_order_acquire))
        {
            /* code */
        }
    }
    void Unlock()
    {
        flag.clear(std::memory_order_release);
    }
private:
    std::atomic_flag flag;
};