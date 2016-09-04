#pragma once
#include "EWGraph.h"
#include <list>
#include <queue>
#include <functional>

class LazyPrimMST
{
	void visitVertex(int v);
public:
	typedef std::list<Edge> MSTEdgesContainer;
	LazyPrimMST(const EWGraph& graph);
	MSTEdgesContainer edges();
	double getWeight();
private:
	MSTEdgesContainer MSTEdges;
	double weight;
	const EWGraph& graph;
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> minPQ;
	std::vector<bool> marked;
};