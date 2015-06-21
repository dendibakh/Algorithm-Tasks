#pragma once

#include "FlowEdge.h"
#include <list>
#include <vector>

class FlowNetwork
{
	void checkVertex(int v) const;
	bool alreadyConnected(int v, int w) const;
public:
	typedef std::list<FlowEdge> EdgesList;
	typedef std::vector<EdgesList> EdgesContainer;

	FlowNetwork(int N);
	void addEdge(const FlowEdge& edge);

	EdgesList getAdjacentVertex(int v) const;
	EdgesList getAllEdges() const;
	int getVertexCount() const;
	int getEdgesCount() const;
	void addFlow(int v, int w, int flow);
	std::string toString() const;
private:
	const int N;
	EdgesContainer vertecies;
};