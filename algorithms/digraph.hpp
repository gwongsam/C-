#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../interface/iconvertible.hpp"

using namespace std;
using namespace interface;

template <typename Node>
class Digraph {
 public:
  Digraph() {}
  Digraph(int v) {}
  size_t Vertices() { return adj_list_.size(); }
  vector<Node> Vertices2() {
    vector<Node> vec;
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

  void AddEdge(Node v, Node w) {
    if (!adj_list_.contains(v)) {
      unordered_set<Node> conn{w};
      adj_list_.emplace(make_pair(v, conn));
      return;
    }
    adj_list_[v].emplace(w);
  }

  unordered_set<Node> Adj(Node v) { return adj_list_[v]; }
  unordered_map<Node, unordered_set<Node>> GetGraph() { return adj_list_; }

 private:
  unordered_map<Node, unordered_set<Node>> adj_list_;
};

namespace cvt {
template <typename Node>
string DiNumericToString(Digraph<Node> &g) {
  string result;
  auto adj_list_ = g.GetGraph();
  for (auto vertices : adj_list_) {
    result += to_string(vertices.first);
    for (auto edge : vertices.second) {
      result += " " + to_string(edge);
    }
    result += "\r\n";
  }
  return std::move(result);
}

// template <typename Node>
// string DiStringToString(Digraph<Node> &g) {
//   string result;
//   auto adj_list_ = g.GetGraph();
//   for (auto vertices : adj_list_) {
//     result += std::to_string(vertices.first);
//     for (auto edge : vertices.second) {
//       result += " " + std::to_string(edge);
//     }
//     result += "\r\n";
//   }
//   return std::move(result);
// }
}  // namespace cvt

template <typename Node>
class DirectedDFS {
 public:
  DirectedDFS(Digraph<Node> &g, Node s) { DFS(g, s); }

  bool Marked(Node v) { return marked_[v]; }

 private:
  void DFS(Digraph<Node> &g, Node v) {
    marked_[v] = true;
    unordered_set<Node> adj = g.Adj(v);
    for (auto &w : adj) {
      if (!marked_[w]) {
        DFS(g, w);
      }
    }
  }

 private:
  unordered_map<Node, bool> marked_;
};

template <typename Node>
class DirectedCycle {
 public:
  DirectedCycle(Digraph<Node> &G) {
    vector<Node> vertices = G.Vertices2();
    for (auto v : vertices) {
      if (!marked[v]) {
        DFS(G, v);
      }
    }
  }

  bool HasCycle() { return cycle.size(); }

 private:
  void DFS(Digraph<Node> &G, Node v) {
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
        cycle = stack<Node>();
        for (Node x = v; x != w; x = edgeTo[x]) {
          cycle.emplace(x);
        }
        cycle.emplace(w);
        cycle.emplace(v);
      }
    }
    onStack[v] = false;
  }

 private:
  unordered_map<Node, bool> marked;
  unordered_map<Node, Node> edgeTo;
  unordered_map<Node, bool> onStack;
  stack<Node> cycle;
};
