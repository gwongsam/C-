#include <algorithm>
#include <functional>
#include <iostream>
#include <mutex>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class ThreadSafeHeap {
 private:
  std::vector<T> data;
  mutable std::mutex m;
  Compare comp;

  void siftUp(int i) {
    while (i > 0 && comp(data[i], data[(i - 1) / 2])) {
      std::swap(data[i], data[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  void siftDown(int i) {
    while (2 * i + 1 < data.size()) {
      int left = 2 * i + 1;
      int right = 2 * i + 2;
      int j = left;
      if (right < data.size() && comp(data[right], data[left])) {
        j = right;
      }
      if (comp(data[i], data[j]) || data[i] == data[j]) {
        break;
      }
      std::swap(data[i], data[j]);
      i = j;
    }
  }

 public:
  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }

  T top() const {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw std::runtime_error("Heap is empty");
    }
    return data.front();
  }

  void push(const T& value) {
    std::lock_guard<std::mutex> lock(m);
    data.push_back(value);
    siftUp(data.size() - 1);
  }

  void pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw std::runtime_error("Heap is empty");
    }
    data[0] = data.back();
    data.pop_back();
    siftDown(0);
  }
};
