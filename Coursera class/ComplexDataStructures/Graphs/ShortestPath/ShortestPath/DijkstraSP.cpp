#include "DijkstraSP.h"
#include <limits>

DijkstraSP::DijkstraSP(const EWDiGraph& graph, int source) : distances(graph.getVertexCount(), std::numeric_limits<double>::max()),
edges(graph.getVertexCount(), Edge(0, 0, 0.0))
{
        distances[source] = 0.0;
        IndexedMinPQ<double> minPQ(graph.getVertexCount());
        minPQ.insert(source, 0.0);

        while (!minPQ.isEmpty())
        {
                int v = minPQ.delMin();
                EWDiGraph::EdgesList adjacent = graph.getAdjacentVertex(v);
                for (auto i = adjacent.begin(); i != adjacent.end(); ++i)
                {
                        relax(minPQ, *i);
                }
        }
}

void DijkstraSP::relax(IndexedMinPQ<double>& minPQ, const Edge& e)
{
        int v = e.from();
        int w = e.to();
        if (distances[w] > distances[v] + e.getWeight())
        {
                distances[w] = distances[v] + e.getWeight();
                edges[w] = e;
                if (minPQ.contains(w))
                        minPQ.decreaseKey(w, distances[w]);
                else
                        minPQ.insert(w, distances[w]);
        }
}

double DijkstraSP::distTo(int v) const
{
        if (!hasPathTo(v))
                return std::numeric_limits<double>::max();
        return distances[v];
}

DijkstraSP::PathToStack DijkstraSP::pathTo(int v) const
{
        DijkstraSP::PathToStack retStack;
        if (!hasPathTo(v))
                return retStack;
        int i = v;
        for (; edges[i].getWeight() != 0.0; i = edges[i].from())
        {
                retStack.push(i);
        }
        retStack.push(i);
        return retStack;
}

bool DijkstraSP::hasPathTo(int v) const
{
        return distances[v] < std::numeric_limits<double>::max();
}