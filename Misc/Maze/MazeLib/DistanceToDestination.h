#pragma once
#include <stack>
#include <queue>
#include "Graph.h"

class DistanceToDestination
{
        static const int nullValue = -1;

        void bfs(const Graph& graph, int v);
public:
        DistanceToDestination(const Graph& graph, int source, const std::vector<bool>& marked);
        int distanceTo(int v) const;
private:
        const Graph& graph;
        std::vector<int> distTo;
        std::vector<bool> marked;
};