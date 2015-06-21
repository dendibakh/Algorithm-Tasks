#include "Graph.h"
#include <sstream>
#include <algorithm>

Graph::Graph(int N) : N(N), vertecies(N, EdgesList())
{
        
}

void Graph::checkVertex(int v) const
{
        if ((v < 0) || v >= N)
                throw std::runtime_error("Invalid vertex");
}

void Graph::addEdge(const Edge& edge)
{
        int v = edge.from();
        int w = edge.to();
        checkVertex(v);
        checkVertex(w);
        if ( (v != w) && (!alreadyConnected(v, w)) )
        {
                vertecies[v].push_back(edge);
                vertecies[w].push_back(Edge(w, v));
        }
}

const Graph::EdgesList& Graph::getAdjacentVertex(int v) const
{
        checkVertex(v);
        return vertecies[v];
}

int Graph::getVertexCount() const
{
        return vertecies.size();
}

int Graph::getEdgesCount() const
{
        int retVal = 0;
        for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
        {
                retVal += i->size();
        }
        return retVal / 2;
}

std::string Graph::toString() const
{
        std::string retVal;
        for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
        {
                int v = i - vertecies.begin();
                for (EdgesList::const_iterator j = i->begin(); j != i->end(); ++j)
                {
                        int w = j->to();
                        if (w > v)
                        {
                                std::stringstream stream;
                                stream << j->toString() << std::endl;
                                retVal += stream.str();
                        }       
                }
        }
        return retVal;
}

bool Graph::alreadyConnected(int v, int w) const
{
        // This method wouldn't take much time, because each vertex can have only 8 adjacent vertecies.
        for (EdgesList::const_iterator i = vertecies[v].begin(); i != vertecies[v].end(); ++i)
        {
                if (i->to() == w)
                        return true;
        }
        return false;
}

Graph::EdgesList Graph::getAllEdges() const
{
        Graph::EdgesList retList;
        for (auto i = vertecies.begin(); i != vertecies.end(); ++i)
        {
                for (auto j = i->begin(); j != i->end(); ++j)
                {
                        int v = j->from();
                        int w = j->to();
                        if (std::find(retList.begin(), retList.end(), Edge(w, v)) == retList.end())
                                retList.push_back(*j);
                }
        }
        return retList;
}