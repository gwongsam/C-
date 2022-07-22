#include <memory>

#include "structure.hpp"

template <typename Comparable>
int BiSearch(std::vector<Comparable>& nums, Comparable target) {
  size_t left = 0;
  size_t right = nums.size();
  while (left <= right) {
    size_t pivet = (left + right) / 2;
    if (nums[pivet] < target) {
      left = pivet + 1;
    } else if (target < nums[pivet]) {
      right = pivet - 1;
    } else {
      return pivet;
    }
  }

  return -1;
}

template <typename Key, typename Value>
class BST : public Bitree<Key, Value> {
 public:
  int Size() { return Size(root); }
  bool Get(Key key, Value& val) {
    std::shared_ptr<Node<Key, Value>> x = Get(root, key);
    if (x == nullptr) {
      return false;
    }
    val = x->val;
    return true;
  }
  void Put(Key key, Value val) { root = Put(root, key, val); }
  // Key Min()
  // {
  // return Min(root)->key;
  // }
  // Key Floor(Key key)
  // {
  // std::shared_ptr<Node> x = Floor(root, key);
  // return x == nullptr ? key : x->key;
  // }
 private:
  size_t Size(std::shared_ptr<Node<Key, Value>> x) {
    return x == nullptr ? 0 : x.N;
  }
  std::shared_ptr<Node<Key, Value>> Get(std::shared_ptr<Node<Key, Value>> x,
                                        Key key) {
    if (x == nullptr) {
      return x;
    }
    if (key < x->key) {
      return Get(x->left, key);
    } else if (key > x->key) {
      return Get(x->right, key);
    } else {
      return x;
    }
  }
  std::shared_ptr<Node<Key, Value>> Put(std::shared_ptr<Node<Key, Value>> x,
                                        Key key, Value val) {
    if (x == nullptr) {
      return std::make_shared<Node<Key, Value>>(key, val);
    }
    if (key < x.key) {
      x->left = Put(x->left, key, val);
    } else if (key > x.key) {
      x->right = Put(x->right, key, val);
    } else {
      x->val = val;
    }
    x->N = Size(x->left) + size(x->right) + 1;

    return x;
  }
  // std::shared_ptr<Node> Min(std::shared_ptr<Node> x)
  // {
  // return x->left == nullptr ? x : Min(x->left);
  // }
  // std::shared_ptr<Node> Floor(std::shared_ptr<Node> x, Key Key)
  // {
  // if (x == nullptr)
  // {
  // return nullptr;
  // }

  // }
 public:
  std::shared_ptr<Node<Key, Value>> root;
};