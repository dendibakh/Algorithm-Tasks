#include "DijkstraSP.h"
#include <limits>

DijkstraSP::DijkstraSP(const Graph& graph, int source) : distances(graph.getVertexCount(), std::numeric_limits<int>::max()), 
edges(graph.getVertexCount(), Edge(0, 0))
{
        distances[source] = 0;
        IndexedMinPQ<int> minPQ(graph.getVertexCount());
        minPQ.insert(source, 0);

        while (!minPQ.isEmpty())
        {
                int v = minPQ.delMin();
                Graph::EdgesList adjacent = graph.getAdjacentVertex(v);
                for (auto i = adjacent.begin(); i != adjacent.end(); ++i)
                {
                        relax(minPQ, *i);
                }
        }
}

void DijkstraSP::relax(IndexedMinPQ<int>& minPQ, const Edge& e)
{
        int v = e.from();
        int w = e.to();
        if (distances[w] > distances[v] + 1)
        {
                distances[w] = distances[v] + 1;
                edges[w] = e;
                if (minPQ.contains(w))
                        minPQ.decreaseKey(w, distances[w]);
                else
                        minPQ.insert(w, distances[w]);
        }
}

int DijkstraSP::distTo(int v) const
{
        if (!hasPathTo(v))
                return std::numeric_limits<int>::max();
        return distances[v];
}

DijkstraSP::PathToStack DijkstraSP::pathTo(int v) const
{
        DijkstraSP::PathToStack retStack;
        if (!hasPathTo(v))
                return retStack;
        int i = v;
        for (; distances[i] != 0; i = edges[i].from())
        {
                retStack.push(i);
        }
        retStack.push(i);
        return retStack;
}

bool DijkstraSP::hasPathTo(int v) const
{
        return distances[v] < std::numeric_limits<int>::max();
}