#pragma once
#include "Graph.h"

class VertexCounter
{
        void dfs(int v);
public:
        VertexCounter(const Graph& graph, const std::vector<bool>& marked, int source, int destination);
        bool destinationIsReachable() const;
        int getCount() const;
private:
        const Graph& graph;
        const int destination;
        int count;
        std::vector<bool> marked;
};