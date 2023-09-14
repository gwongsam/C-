#pragma once
#include <atomic>
#include <iostream>
#include <memory>

template <typename T>
class LockFreeStack {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& data) : data(data), next(nullptr) {}
  };

  std::atomic<Node*> head;

 public:
  LockFreeStack() : head(nullptr) {}

  ~LockFreeStack() {
    while (Node* oldHead = head.load()) {
      head.store(oldHead->next);
      delete oldHead;
    }
  }

  void push(const T& data) {
    Node* newNode = new Node(data);
    newNode->next = head.load();
    while (!head.compare_exchange_weak(newNode->next, newNode))
      ;  // CAS loop
  }

  bool pop(T& result) {
    Node* currentHead = head.load();
    while (currentHead &&
           !head.compare_exchange_weak(currentHead, currentHead->next))
      ;  // CAS loop
    if (currentHead) {
      result = currentHead->data;
      delete currentHead;
      return true;
    }
    return false;
  }
};
