#pragma once
#include <queue>
#include <memory>
#include <functional>
template <typename Key, typename Value>
class Node
{
public:
    Node(Key key_, Value &&val_, size_t N_ = 1, std::shared_ptr<Node> left_ = nullptr, std::shared_ptr<Node> right_ = nullptr)
        : key(key_), val(val_), N(N_), left(left_), right(right_) {}

public:
    Key key;
    Value val;
    size_t N;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

template <typename T>
class Heap
{
public:
};

template <typename Key, typename Value>
class Bitree
{
public:
    Bitree() {}
    virtual int BFS(std::function<void(Value &)> F, std::shared_ptr<Node<Key, Value>> &node)
    {
        std::queue<std::shared_ptr<Node<Key, Value>>> q;
        q.emplace(node);
        while (!q.empty())
        {
            std::shared_ptr<Node<Key, Value>> n = q.front();
            q.pop();
            F(n->val);
            if (n->left != nullptr)
            {
                q.emplace(n->left);
            }
            if (n->right != nullptr)
            {
                q.emplace(n->right);
            }
        }
        return 0;
    }
    virtual int DFS(std::function<void(Value &)> F, std::shared_ptr<Node<Key, Value>> &node)
    {
        F(node->val);
        if (node->left != nullptr)
        {
            DFS(F, node->left);
        }
        if (node->right != nullptr)
        {
            DFS(F, node->right);
        }

        return 0;
    }

public:
};