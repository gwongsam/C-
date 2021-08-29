#include <memory>
#include "structure.hpp"

class binary_tree
{
public:
    
public:
   std::shared_ptr<binary_tree> left;
   std::shared_ptr<binary_tree> right;
   
};

template <typename Key, typename Value>
class BST
{
public:
   int Size()
   {
      return Size(root);
   }
   bool Get(Key key, Value &val)
   {
      std::shared_ptr<Node<Key, Value>> x = Get(root, key);
      if (x == nullptr)
      {
         return false;
      }
      val = x->val;
      return true;
   }
   void Put(Key key, Value val)
   {
      root = Put(root, key, val);
   }
private:
   size_t Size(std::shared_ptr<Node<Key, Value>> x)
   {
      return x == nullptr ? 0 : x.N;
   }
   std::shared_ptr<Node<Key, Value>> Get(std::shared_ptr<Node<Key, Value>> x, Key key)
   {
      if (x == nullptr)
      {
         return x;
      }
      if (key < x->key)
      {
         return Get(x->left, key);
      }
      else if (key > x->key)
      {
         return Get(x->right, key);
      }
      else
      {
         return x;
      }
   }
   std::shared_ptr<Node<Key, Value>> Put(std::shared_ptr<Node<Key, Value>> x, Key key, Value val)
   {
      if (x == nullptr)
      {
         return std::make_shared<Node<Key, Value>>(key, val);
      }
      if (key < x.key)
      {
         x->left = Put(x->left, key, val);
      }
      else if (key > x.key)
      {
         x->right = Put(x->right, key, val);
      }
      else
      {
         x->val = val;
      }
      x->N = Size(x->left) + size(x->right) + 1;
      
      return x;
   }
public:
   std::shared_ptr<Node<Key, Value>> root;
};