#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../interface/iconvertible.hpp"

using namespace std;
using namespace interface;

class Digraph : public IConvertible
{
public:
    Digraph() {}
    Digraph(int v)
    {
    }
    size_t Vertices() { return adj_list_.size(); }
    size_t Edges()
    {
        size_t size = 0;
        for (auto vertices : adj_list_)
        {
            size += vertices.second.size();
        }
        return size;
    }

    void AddEdge(size_t v, size_t w)
    {
        if (!adj_list_.contains(v))
        {
            unordered_set<size_t> conn{w};
            adj_list_.emplace(make_pair(v, conn));
            return;
        }
        adj_list_[v].emplace(w);
    }

    unordered_set<size_t> Adj(size_t v)
    {
        return adj_list_[v];
    }

    string ToString() override
    {
        string result;
        for (auto vertices : adj_list_)
        {
            result += std::to_string(vertices.first);
            for (auto edge : vertices.second)
            {
                result += " " + std::to_string(edge);
            }
            result += "\r\n";
        }
        return std::move(result);
    }

private:
    unordered_map<size_t, unordered_set<size_t>> adj_list_;
};

class DirectedDFS
{
public:
    DirectedDFS(Digraph g, size_t s)
    {
        marked_.resize(g.Vertices(), false);
        DFS(g, s);
    }

    bool Marked(size_t v)
    {
        return marked_[v];
    }

private:
    void DFS(Digraph g, size_t v)
    {
        marked_[v] = true;
        unordered_set<size_t> adj = g.Adj(v);
        for (auto &w : adj)
        {
            if (!marked_[w])
            {
                DFS(g, w);
            }
        }
    }

private:
    vector<bool> marked_;
};