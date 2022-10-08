#pragma once
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
template <typename T>
class threadsafe_queue {
 private:
  mutable std::mutex mut_;
  std::queue<T> data_queue_;
  std::condition_variable data_cond_;

 public:
  threadsafe_queue() {}
  threadsafe_queue(const threadsafe_queue &other) {
    std::lock_guard<std::mutex> lk(other.mut_);
    data_queue_ = other.data_queue_;
  }
  threadsafe_queue &operator=(const threadsafe_queue &) = delete;
  ~threadsafe_queue(){};
  void push(T new_value) {
    std::lock_guard<std::mutex> lk(mut_);
    data_queue_.push(new_value);
    data_cond_.notify_one();
  }
  bool try_pop(T &value) {
    std::lock_guard<std::mutex> lk(mut_);
    if (data_queue_.empty()) {
      return false;
    }
    value = data_queue_.front();
    data_queue_.pop();
    return true;
  }
  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lk(mut_);
    if (data_queue_.empty()) {
      return std::shared_ptr<T>();
    }
    std::shared_ptr<T> res(std::make_shared<T>(data_queue_.front()));
    data_queue_.pop();
    return res;
  }
  void wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lk(mut_);
    data_cond_.wait(lk, [this] { return !data_queue_.empty(); });
    value = data_queue_.front();
    data_queue_.pop();
  }
  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lk(mut_);
    // data_cond_.wait(lk, [this] { return !data_queue.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(data_queue_.front()));
    // value = data_queue.front();
    data_queue_.pop();
    return res;
  }
  bool empty() const {
    std::lock_guard<std::mutex> lk(mut_);
    return data_queue_.empty();
  }
};

namespace algo {
template <typename T>
class queue {
 private:
  struct node {
    T data;
    std::unique_ptr<node> next;
    node(T data_) : data(std::move(data_)) {}
  };
  std::unique_ptr<node> head;
  node *tail;

 public:
  queue() : tail(nullptr) {}
  queue(const &queue other) = delete;
  queue &operator=(const queue &other) = delete;

  std::shared_ptr<T> try_pop() {
    if (!head) {
      return shared_ptr<T>();
    }
    std::shared_ptr<T> const res(std::make_shared<T>(std::move(head->data)));
    std::unique_ptr<node> const old_head = std::move(head);
    head = std::move(old_head->next);
    if (!head) {
      tail = nullptr;
    }
    return res;
  }

  void push(T new_value) {
    std::unique_ptr<node> p(new node(std::move(new_value)));
    node *const new_tail = p.get();
    if (tail) {
      tail->next = std::mvoe(p);
    } else {
      head = std::move(p);
    }
    tail = new_tail;
  }
};
}  // namespace algo
