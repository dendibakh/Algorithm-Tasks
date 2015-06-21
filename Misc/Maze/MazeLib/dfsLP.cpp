#pragma once
#include "dfsLP.h"
#include "VertexCounter.h"
#include "DistanceToDestination.h"
#include <map>

dfsLP::dfsLP(const Graph& graph, int source, int destination) : graph(graph), source(source), destination(destination), distance(0)
{
        if ((source < 0) || source >= graph.getVertexCount())
                throw std::runtime_error("Invalid source vertex");
        
        std::vector<bool> marked(graph.getVertexCount(), false);
        VertexCounter counter(graph, marked, source, destination);
        maxdistance = counter.getCount() - 1;
        std::vector<int> edgeTo(graph.getVertexCount(), -1);
        dfs(source, marked, edgeTo, 0);
}

// Each recursion level explore new available path
// This method assume marked vector by value, to explore new available path
void dfsLP::dfs(int v, std::vector<bool> marked, std::vector<int>& curedgeTo, int currentDistance)
{
        marked[v] = true;
        ++currentDistance;
        
        std::list<int> filteredVertecies;
        const Graph::EdgesList& list = graph.getAdjacentVertex(v);
        for (Graph::EdgesList::const_iterator i = list.begin(); i != list.end(); ++i)
        {
                int w = i->to();
                if (!marked[w])
                {
                        // if we found destination vertex, there is no need to recursively visit it, because it's the last vertex in the path
                        if (w == destination)
                        {
                                if (distance < currentDistance)
                                {
                                        edgeTo = curedgeTo;
                                        distance = currentDistance;
                                        edgeTo[w] = v;
                                }
                        }
                        else
                        {
                            // our prunning rule: 1. if a vertex to explore doesn't have a path to the destination vertex, it's no need to explore that vertex.
                            //                    2. if amount of reachable vertecies from vertex to explore plus already explored vertecies is less than best longest way, 
                            //                       found so far, it's no need to explore that vertex. E.g. we can't find a better way by exploring that path.
                            VertexCounter counter(graph, marked, w, destination);
                            if (counter.destinationIsReachable() && (distance < currentDistance - 1 + counter.getCount()))
                            {
                               filteredVertecies.push_back(w);
                            }
                        }
                }
        }

        if (filteredVertecies.size() == 1)
        {
           // if it's the only one found way, so lets explore it
           recursivelyRunDFS(v, (*filteredVertecies.begin()), marked, curedgeTo, currentDistance);
           if (distance == maxdistance)
              return; // we've already found longest path
        }
        else
        {
           // our algorithm is greedy, we explore possible variants in the order of decreasing distance from destination
           std::multimap<int, int> explorationOrder;
           for (auto i = filteredVertecies.begin(); i != filteredVertecies.end(); ++i)
           {
              DistanceToDestination dtd(graph, *i, marked);
              explorationOrder.insert(std::make_pair(dtd.distanceTo(destination), *i));         
           }
           for (auto i = explorationOrder.rbegin(); i != explorationOrder.rend(); ++i)
           {
              recursivelyRunDFS(v, i->second, marked, curedgeTo, currentDistance);
              if (distance == maxdistance)
                 return; // we've already found longest path
           }
        }
}

void dfsLP::recursivelyRunDFS(int v, int w, const std::vector<bool>& marked, const std::vector<int>& curedgeTo, int currentDistance)
{
   std::vector<int> newEdgeTo(curedgeTo);
   newEdgeTo[w] = v;
   dfs(w, marked, newEdgeTo, currentDistance);
}
        
bool dfsLP::hasPath() const
{
        return distance != 0;
}

dfsLP::VertexStack dfsLP::getPath() const
{
        VertexStack st;
        if (!hasPath())
                return st;
        for (int i = destination; i != source; i = edgeTo[i])
        {
                st.push(i);
        }
        st.push(source);
        return st;
}

int dfsLP::getDistance() const
{
        return distance;
}