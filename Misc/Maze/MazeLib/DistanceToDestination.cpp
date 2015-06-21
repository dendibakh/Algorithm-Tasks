#include "DistanceToDestination.h"

void DistanceToDestination::bfs(const Graph& graph, int v)
{
        std::queue<int> vertecies;
        vertecies.push(v);
        distTo[v] = 0;
        while (!vertecies.empty())
        {
                int current = vertecies.front();
                vertecies.pop();
                marked[v] = true;
                Graph::EdgesList list = graph.getAdjacentVertex(current);
                for (auto i = list.begin(); i != list.end(); ++i)
                {
                        int adjacent = i->to();
                        if ((!marked[adjacent]) && (nullValue == distTo[adjacent]))
                        {
                                vertecies.push(adjacent);
                                distTo[adjacent] = distTo[current] + 1;
                        }
                }
        }
}

DistanceToDestination::DistanceToDestination(const Graph& graph, int source, const std::vector<bool>& marked) : graph(graph), marked(marked), distTo(graph.getVertexCount(), nullValue)
{
        if ((source < 0) || source >= graph.getVertexCount())
                throw std::runtime_error("Invalid source vertex");
        bfs(graph, source);
}

int DistanceToDestination::distanceTo(int v) const
{
        if (nullValue == distTo[v])
                throw std::runtime_error("There is no path to that vertex");
        return distTo[v];
}