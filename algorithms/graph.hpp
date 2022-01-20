#pragma once
#include <set>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include "../public/public.hpp"
#include "../interface/iconvertible.hpp"
using namespace std;
using namespace interface;

namespace graph
{
    class Graph : public IConvertible
    {
    public:
        Graph() {}

        void AddEdge(int v, int w)
        {
            if (!adj_list_.contains(v))
            {
                set<int> s{w};
                adj_list_.emplace(std::make_pair(v, move(s)));
            }
            else
            {
                adj_list_[v].emplace(w);
            }
            if (!adj_list_.contains(w))
            {
                set<int> s{v};
                adj_list_.emplace(std::make_pair(w, move(s)));
            }
            else
            {
                adj_list_[w].emplace(v);
            }
        }

        void ReadGraph(std::string pwd)
        {
            std::vector<std::string> data = Public::ReadLines(pwd);
            for (size_t i = 2; i < data.size(); i++)
            {
                std::vector<std::string> line = Public::SplitDelim(data[i], " ");
                if (line.size() < 2)
                {
                    continue;
                }
                AddEdge(std::stoi(line[0]), std::stoi(line[1]));
            }
        }

        size_t Vertices() { return adj_list_.size(); }

        size_t Edges()
        {
            size_t edges = 0;
            for (auto item : adj_list_)
            {
                edges += item.second.size();
            }
            if (edges % 2 != 0)
                throw invalid_argument("wrong edges can not be modulo");
            edges /= 2;
            return edges;
        }

        string ToString() override
        {
            std::string str;
            for (auto &item : adj_list_)
            {
                str += std::to_string(item.first);
                for (auto &edge : item.second)
                {
                    str += " " + std::to_string(edge);
                }
                str += "\n";
            }
            return str;
        }

    private:
        unordered_map<int, set<int>> adj_list_;
    };

    class Search
    {
    public:
        Search(Graph g, int s)
        {
        }
        bool Marked(int v)
        {
            bool status = false;

            return status;
        }
        int Count()
        {
            return 0;
        }
    };

    class DepthFirstSearch
    {
    public:
        DepthFirstSearch(Graph g, int s)
        {
        }
        void DFS(Graph g, int v)
        {
        }
        bool Marked(int w)
        {
            return true;
        }
        int Count()
        {
            return count;
        }

    private:
        bool marked[10];
        int count;
    };

    class Paths
    {
    public:
        Paths(Graph g, int s)
        {
        }
        bool HasPathTo(int v)
        {
            return true;
        }
    };

    class BreadthFirstPaths
    {
    public:
        BreadthFirstPaths(Graph g, int s)
        {
        }
        bool HasPathTo(int v)
        {
            return true;
        }

    private:
        void BFS(Graph g, int s)
        {
        }
        vector<bool> marked_;
        vector<int> edgeto_;
        int s;
    };
}
