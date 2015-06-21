#pragma once
#include "Graph.h"
#include "IndexedMinPQ.h"
#include <stack>

class DijkstraSP
{
        void relax(IndexedMinPQ<int>& minPQ, const Edge& e);
public:
        typedef std::stack<int> PathToStack;

        DijkstraSP(const Graph& graph, int source);
        DijkstraSP(const DijkstraSP& rhs) = default;
        DijkstraSP& operator=(const DijkstraSP& rhs) = default;

        int distTo(int v) const;
        PathToStack pathTo(int v) const;
        bool hasPathTo(int v) const;
private:
        std::vector<int> distances;
        std::vector<Edge> edges;
};