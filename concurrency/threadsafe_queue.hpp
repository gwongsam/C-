#pragma once
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

template <typename T>
class threadsafe_queue {
 private:
  struct node {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
  };
  std::mutex head_mutex;
  std::unique_ptr<node> head;
  std::mutex tail_mutex;
  node *tail;

 private:
  node *get_tail() {
    std::lock_guard<std::mutex> tail_lock(tail_mutex);
    return tail;
  }

  std::unique_ptr<node> pop_head() {
    std::lock_guard<std::mutex> head_lock(head_mutex);

    if (head.get() == get_tail()) {
      return nullptr;
    }
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return old_head;
  }

 public:
  threadsafe_queue() : head(new node), tail(head.get()) {}
  threadsafe_queue(const threadsafe_queue &other) = delete;
  threadsafe_queue &operator=(const threadsafe_queue &other) = delete;

  std::shared_ptr<T> try_pop() {
    std::unique_ptr<node> old_head = pop_head();
    return old_head ? old_head->data : std::shared_ptr<T>();
  }

  void push(T new_value) {
    std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
    std::unique_ptr<node> p(new_value);
    node *const new_tail = p.get();
    std::lock_guard<std::mutex> tail_lock(tail_mutex);
    tail->data = new_data;
    tail->next = std::move(p);
    tail = new_tail;
  }
};

namespace task {
template <typename T>
class Queue {
 private:
  struct node {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
    node(T data_) : data(std::move(data_)) {}
  };
  std::unique_ptr<node> head;
  node *tail;

 public:
  Queue() : head(new node), tail(head.get()) {}
  Queue(Queue const &other) = delete;
  Queue &operator=(Queue const &other) = delete;

  std::shared_ptr<T> try_pop() {
    if (head.get() == tail) {
      return shared_ptr<T>();
    }
    std::shared_ptr<T> const res(head->data);
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return res;
  }

  void push(T new_value) {
    std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
    std::unique_ptr<node> p(new node);
    tail->data = new_data;
    node *const new_tail = p.get();
    tail->next = std::move(p);
    tail = new_tail;
  }
};
}  // namespace task
