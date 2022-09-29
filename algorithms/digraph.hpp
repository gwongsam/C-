#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../interface/iconvertible.hpp"

using namespace std;
using namespace interface;

class Digraph : public IConvertible {
 public:
  Digraph() {}
  Digraph(int v) {}
  size_t Vertices() { return adj_list_.size(); }
  vector<size_t> Vertices2() {
    vector<size_t> vec;
    for (auto item : adj_list_) {
      vec.emplace_back(item.first);
    }
    return vec;
  }
  size_t Edges() {
    size_t size = 0;
    for (auto vertices : adj_list_) {
      size += vertices.second.size();
    }
    return size;
  }

  void AddEdge(size_t v, size_t w) {
    if (!adj_list_.contains(v)) {
      unordered_set<size_t> conn{w};
      adj_list_.emplace(make_pair(v, conn));
      return;
    }
    adj_list_[v].emplace(w);
  }

  unordered_set<size_t> Adj(size_t v) { return adj_list_[v]; }

  string ToString() override {
    string result;
    for (auto vertices : adj_list_) {
      result += std::to_string(vertices.first);
      for (auto edge : vertices.second) {
        result += " " + std::to_string(edge);
      }
      result += "\r\n";
    }
    return std::move(result);
  }

 private:
  unordered_map<size_t, unordered_set<size_t>> adj_list_;
};

class DirectedDFS {
 public:
  DirectedDFS(Digraph &g, size_t s) { DFS(g, s); }

  bool Marked(size_t v) { return marked_[v]; }

 private:
  void DFS(Digraph &g, size_t v) {
    marked_[v] = true;
    unordered_set<size_t> adj = g.Adj(v);
    for (auto &w : adj) {
      if (!marked_[w]) {
        DFS(g, w);
      }
    }
  }

 private:
  unordered_map<size_t, bool> marked_;
};

class DirectedCycle {
 public:
  DirectedCycle(Digraph &G) {
    vector<size_t> vertices = G.Vertices2();
    for (auto v : vertices) {
      if (!marked[v]) {
        DFS(G, v);
      }
    }
  }

  bool HasCycle() { return cycle.size(); }

 private:
  void DFS(Digraph &G, size_t v) {
    onStack[v] = true;
    marked[v] = true;
    auto adj = G.Adj(v);
    for (auto w : adj) {
      if (HasCycle()) {
        return;
      } else if (!marked[w]) {
        edgeTo[w] = v;
        DFS(G, w);
      } else if (onStack[w]) {
        cycle = stack<size_t>();
        for (size_t x = v; x != w; x = edgeTo[x]) {
          cycle.emplace(x);
        }
        cycle.emplace(w);
        cycle.emplace(v);
      }
    }
    onStack[v] = false;
  }

 private:
  unordered_map<size_t, bool> marked;
  unordered_map<size_t, size_t> edgeTo;
  unordered_map<size_t, bool> onStack;
  stack<size_t> cycle;
};
