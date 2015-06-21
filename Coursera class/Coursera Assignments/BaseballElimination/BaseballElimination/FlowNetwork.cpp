#include "FlowNetwork.h"
#include <sstream>

FlowNetwork::FlowNetwork(int N) : N(N), vertecies(N, EdgesList())
{

}

void FlowNetwork::checkVertex(int v) const
{
	if ((v < 0) || v >= N)
		throw std::runtime_error("Invalid vertex");
}

void FlowNetwork::addEdge(const FlowEdge& edge)
{
	int v = edge.from();
	int w = edge.to();
	checkVertex(v);
	checkVertex(w);
	if (!alreadyConnected(v, w))
	{
		vertecies[v].push_back(edge);
		vertecies[w].push_back(edge);
	}
}

FlowNetwork::EdgesList FlowNetwork::getAdjacentVertex(int v) const
{
	checkVertex(v);
	return vertecies[v];
}

int FlowNetwork::getVertexCount() const
{
	return N;
}

int FlowNetwork::getEdgesCount() const
{
	int retVal = 0;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		retVal += i->size();
	}
	return retVal / 2;
}

std::string FlowNetwork::toString() const
{
	std::string retVal;
	for (std::vector<EdgesList>::const_iterator i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		int v = i - vertecies.begin();
		for (EdgesList::const_iterator j = i->begin(); j != i->end(); ++j)
		{
			if (j->from() == v)
			{
				std::stringstream stream;
				stream << j->toString() << std::endl;
				retVal += stream.str();
			}
		}
	}
	return retVal;
}

bool FlowNetwork::alreadyConnected(int v, int w) const
{
	for (EdgesList::const_iterator i = vertecies[v].begin(); i != vertecies[v].end(); ++i)
	{
		if (i->to() == w)
			return true;
	}
	return false;
}

FlowNetwork::EdgesList FlowNetwork::getAllEdges() const
{
	FlowNetwork::EdgesList retList;
	for (auto i = vertecies.begin(); i != vertecies.end(); ++i)
	{
		int v = i - vertecies.begin();
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			if (j->from() == v)
				retList.push_back(*j);
		}
	}
	return retList;
}

void FlowNetwork::addFlow(int v, int w, int flow)
{
	checkVertex(v);
	checkVertex(w);
	for (auto i = vertecies[v].begin(); i != vertecies[v].end(); ++i)
	{
		if (i->other(v) == w)
			i->addResidualFlowTo(w, flow);
	}
	for (auto i = vertecies[w].begin(); i != vertecies[w].end(); ++i)
	{
		if (i->other(w) == v)
			i->addResidualFlowTo(w, flow);
	}
}