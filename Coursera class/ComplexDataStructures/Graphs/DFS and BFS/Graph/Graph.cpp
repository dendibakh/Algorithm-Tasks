#include "Graph.h"
#include <sstream>
#include <algorithm>

Graph::Graph(int N) : N(N), vertecies(N, std::list<int>())
{
	
}

void Graph::checkVertex(int v) const
{
	if ((v < 0) || v >= N)
		throw std::runtime_error("Invalid vertex");
}

void Graph::addEdge(int v, int w)
{
	checkVertex(v);
	checkVertex(w);
	if (!alreadyConnected(v, w))
	{
		vertecies[v].push_back(w);
		if (v != w)
			vertecies[w].push_back(v);
	}
}

Graph::EdgesList Graph::getAdjacentVertex(int v) const
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
			int w = *j;
			if (w > v)
			{
				std::stringstream stream;
				stream << v << " - " << w << std::endl;
				retVal += stream.str();
			}
		}
	}
	return retVal;
}

int Graph::degree(int v) const
{
	checkVertex(v);
	return vertecies[v].size();
}

int Graph::maxdegree() const
{
	unsigned int retVal = 0;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		retVal = std::max(retVal, i->size());
	}
	return retVal;
}

double Graph::averagedegree() const
{
	double retVal = 0;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		retVal += i->size();
	}
	return retVal / vertecies.size();
}

int Graph::numberOfSelfLoops() const
{
	int retVal = 0;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		int v = i - vertecies.begin();
		for (EdgesList::const_iterator j = i->begin(); j != i->end(); ++j)
		{
			int w = *j;
			if (w == v)
				++retVal;
		}
	}
	return retVal;
}

bool Graph::alreadyConnected(int v, int w) const
{
	for (EdgesList::const_iterator i = vertecies[v].begin(); i != vertecies[v].end(); ++i)
	{
		if (*i == w)
			return true;
	}
	return false;
}