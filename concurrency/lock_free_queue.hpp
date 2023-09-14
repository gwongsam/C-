#include <atomic>
#include <memory>

template <typename T>
class LockFreeQueue {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& data) : data(data), next(nullptr) {}
  };

  std::atomic<Node*> head;
  std::atomic<Node*> tail;

 public:
  LockFreeQueue() : head(nullptr), tail(nullptr) {}

  ~LockFreeQueue() {
    while (Node* oldHead = head.load()) {
      head.store(oldHead->next);
      delete oldHead;
    }
  }

  void enqueue(const T& data) {
    Node* newNode = new Node(data);
    newNode->next = nullptr;
    Node* oldTail = tail.exchange(newNode);
    if (oldTail) {
      oldTail->next = newNode;
    } else {
      // Queue was empty, update head to newNode
      head.store(newNode);
    }
  }

  bool dequeue(T& result) {
    Node* currentHead = head.load();
    while (currentHead) {
      if (head.compare_exchange_weak(currentHead, currentHead->next)) {
        result = currentHead->data;
        delete currentHead;
        return true;
      }
    }
    return false;  // Queue was empty
  }
};
