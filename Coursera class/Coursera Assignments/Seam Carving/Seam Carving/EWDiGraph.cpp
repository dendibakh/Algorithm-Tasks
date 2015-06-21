#include "EWDiGraph.h"
#include <sstream>
#include <algorithm>
#include <algorithm>

EWDiGraph::EWDiGraph(int N) : N(N), vertecies(N, EdgesList())
{

}

void EWDiGraph::checkVertex(int v) const
{
   if ((v < 0) || v >= N)
      throw std::runtime_error("Invalid vertex");
}

void EWDiGraph::addEdge(const Edge& edge)
{
   int v = edge.from();
   int w = edge.to();
   checkVertex(v);
   checkVertex(w);
   if (!alreadyConnected(v, w))
   {
      vertecies[v].push_back(edge);
   }
}

const EWDiGraph::EdgesList& EWDiGraph::getAdjacentVertex(int v) const
{
   checkVertex(v);
   return vertecies[v];
}

int EWDiGraph::getVertexCount() const
{
   return vertecies.size();
}

int EWDiGraph::getEdgesCount() const
{
   int retVal = 0;
   for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
   {
      retVal += i->size();
   }
   return retVal;
}

std::string EWDiGraph::toString() const
{
   std::string retVal;
   for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
   {
      for (EdgesList::const_iterator j = i->begin(); j != i->end(); ++j)
      {
         std::stringstream stream;
         stream << j->toString() << std::endl;
         retVal += stream.str();
      }
   }
   return retVal;
}

bool EWDiGraph::alreadyConnected(int v, int w) const
{
   for (EdgesList::const_iterator i = vertecies[v].begin(); i != vertecies[v].end(); ++i)
   {
      if (i->to() == w)
         return true;
   }
   return false;
}

EWDiGraph::EdgesList EWDiGraph::getAllEdges() const
{
   EWDiGraph::EdgesList retList;
   for (auto i = vertecies.begin(); i != vertecies.end(); ++i)
   {
      for (auto j = i->begin(); j != i->end(); ++j)
      {
         retList.push_back(*j);
      }
   }
   return retList;
}

EWDiGraph EWDiGraph::getNegated() const
{
   EWDiGraph negated(this->getVertexCount());
   for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
   {
      for (auto j = i->begin(); j != i->end(); ++j)
      {
         negated.addEdge(Edge(j->from(), j->to(), -j->getWeight()));
      }
   }
   return negated;
}