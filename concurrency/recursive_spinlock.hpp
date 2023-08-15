#include <atomic>
#include <thread>

class RecursiveSpinLock {
 private:
  std::atomic<std::thread::id> ownerThread;
  std::atomic<int> lockCount;

 public:
  RecursiveSpinLock() : ownerThread(), lockCount(0) {}

  void lock() {
    auto currentThreadId = std::this_thread::get_id();

    // If the current thread already owns the lock, just increase the counter.
    if (ownerThread.load() == currentThreadId) {
      lockCount.fetch_add(1);
      return;
    }

    // Otherwise, spin until we get the lock.
    while (true) {
      std::thread::id noThread;
      if (ownerThread.compare_exchange_weak(noThread, currentThreadId)) {
        lockCount.store(1);
        break;
      }
    }
  }

  void unlock() {
    if (--lockCount == 0) {
      ownerThread.store(std::thread::id());
    }
  }
};
