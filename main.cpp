#include "main.hpp"

void printNumber(int x) { std::cout << "Number: " << x << std::endl; }

int main() {
  ThreadPool pool(4);

  for (int i = 0; i < 10; i++) {
    pool.enqueue(i, [i]() {
      std::this_thread::sleep_for(std::chrono::seconds(i));
      printNumber(i);
    });
  }

  // Give threads a moment to execute
  std::this_thread::sleep_for(std::chrono::seconds(2));

  return 0;
}
