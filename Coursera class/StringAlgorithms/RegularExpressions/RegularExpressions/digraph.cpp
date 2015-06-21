#include "digraph.h"
#include <sstream>
#include <algorithm>

DiGraph::DiGraph(int N) : N(N), vertecies(N, std::list<int>())
{

}

void DiGraph::checkVertex(int v) const
{
	if ((v < 0) || v >= N)
		throw std::runtime_error("Invalid vertex");
}

void DiGraph::addEdge(int v, int w)
{
	checkVertex(v);
	checkVertex(w);
	if (!alreadyConnected(v, w))
		vertecies[v].push_back(w); 
}

DiGraph::EdgesList DiGraph::getAdjacentVertex(int v) const
{
	checkVertex(v);
	return vertecies[v];
}

int DiGraph::getVertexCount() const
{
	return vertecies.size();
}

int DiGraph::getEdgesCount() const
{
	int retVal = 0;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		retVal += i->size();
	}
	return retVal;
}

std::string DiGraph::toString() const
{
	std::string retVal;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		int v = i - vertecies.begin();
		for (EdgesList::const_iterator j = i->begin(); j != i->end(); ++j)
		{
			std::stringstream stream;
			stream << v << " -> " << *j << std::endl;
			retVal += stream.str();
		}
	}
	return retVal;
}

int DiGraph::degree(int v) const
{
	checkVertex(v);
	return vertecies[v].size();
}

int DiGraph::maxdegree() const
{
	unsigned int retVal = 0;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		retVal = std::max(retVal, i->size());
	}
	return retVal;
}

double DiGraph::averagedegree() const
{
	double retVal = 0;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		retVal += i->size();
	}
	return retVal / vertecies.size();
}

int DiGraph::numberOfSelfLoops() const
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

bool DiGraph::alreadyConnected(int v, int w) const
{
	for (EdgesList::const_iterator i = vertecies[v].begin(); i != vertecies[v].end(); ++i)
	{
		if (*i == w)
			return true;
	}
	return false;
}

DiGraph DiGraph::getReversed() const
{
	DiGraph reversed(this->getVertexCount());
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		int index = i - vertecies.begin();
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			reversed.addEdge(*j, index);
		}
	}
	return reversed;
}

bool DiGraph::operator==(const DiGraph& rhs)
{
	if (N != rhs.N)
		return false;
	for (int i = 0; i < N; ++i)
	{
		if (vertecies[i].size() != rhs.vertecies[i].size())
			return false;
		std::vector<EdgesList> first(vertecies[i].begin(), vertecies[i].end());
		std::vector<EdgesList> second(rhs.vertecies[i].begin(), rhs.vertecies[i].end());
		std::sort(first.begin(), first.end());
		std::sort(second.begin(), second.end());
		if (!std::equal(first.begin(), first.end(), second.begin()))
			return false;
	}
	return true;
}