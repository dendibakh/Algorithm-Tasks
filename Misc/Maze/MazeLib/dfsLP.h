#pragma once
#include <stack>
#include <vector>
#include "Graph.h"

class dfsLP
{
        void dfs(int v, std::vector<bool> marked, std::vector<int>& curedgeTo, int currentDistance);
        void recursivelyRunDFS(int v, int w, const std::vector<bool>& marked, const std::vector<int>& curedgeTo, int currentDistance);
public:
        typedef std::stack<int> VertexStack;

        dfsLP(const Graph& graph, int source, int destination);
        dfsLP(const dfsLP& rhs) = default;
        dfsLP& operator=(const dfsLP& rhs) = default;

        bool hasPath() const;
        VertexStack getPath() const;
        int getDistance() const;
private:
        const Graph& graph;
        const int source;
        const int destination;
        std::vector<int> edgeTo;
        int distance;
        int maxdistance;
};