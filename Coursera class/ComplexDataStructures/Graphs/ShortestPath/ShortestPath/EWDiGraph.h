#pragma once
#include <list>
#include <string>
#include <vector>
#include "Edge.h"

class EWDiGraph
{
	void checkVertex(int v) const;
	bool alreadyConnected(int v, int w) const;
public:
	typedef std::list<Edge> EdgesList;
	typedef std::vector<EdgesList> EdgesContainer;
	EWDiGraph(int N);
	void addEdge(const Edge& edge);
	EdgesList getAdjacentVertex(int v) const;
	EdgesList getAllEdges() const;
	int getVertexCount() const;
	int getEdgesCount() const;
	std::string toString() const;
	EWDiGraph getNegated() const;
private:
	const int N;
	EdgesContainer vertecies;
};