#include "EWGraph.h"
#include <sstream>
#include <algorithm>
#include <algorithm>

EWGraph::EWGraph(int N) : N(N), vertecies(N, EdgesList())
{
	
}

void EWGraph::checkVertex(int v) const
{
	if ((v < 0) || v >= N)
		throw std::runtime_error("Invalid vertex");
}

void EWGraph::addEdge(const Edge& edge)
{
	int v = edge.either();
	int w = edge.other(v);
	checkVertex(v);
	checkVertex(w);
	if (!alreadyConnected(v, w))
	{
		vertecies[v].push_back(edge);
		if (v != w)
		{
			int v1 = edge.either();
			int w1 = edge.other(v1);
			vertecies[w].push_back(Edge(w1, v1, edge.getWeight()));
		}
	}
}

EWGraph::EdgesList EWGraph::getAdjacentVertex(int v) const
{
	checkVertex(v);
	return vertecies[v];
}

int EWGraph::getVertexCount() const
{
	return vertecies.size();
}

int EWGraph::getEdgesCount() const
{
	int retVal = 0;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		retVal += i->size();
	}
	return retVal / 2;
}

std::string EWGraph::toString() const
{
	std::string retVal;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		int v = i - vertecies.begin();
		for (EdgesList::const_iterator j = i->begin(); j != i->end(); ++j)
		{
			int w = j->other(v);
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

bool EWGraph::alreadyConnected(int v, int w) const
{
	for (EdgesList::const_iterator i = vertecies[v].begin(); i != vertecies[v].end(); ++i)
	{
		if (i->other(v) == w)
			return true;
	}
	return false;
}

EWGraph::EdgesList EWGraph::getAllEdges() const
{
	EWGraph::EdgesList retList;
	for (auto i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			int v = j->either();
			int w = j->other(v);
			if (std::find(retList.begin(), retList.end(), Edge(w, v, j->getWeight())) == retList.end())
				retList.push_back(*j);
		}
	}
	return retList;
}