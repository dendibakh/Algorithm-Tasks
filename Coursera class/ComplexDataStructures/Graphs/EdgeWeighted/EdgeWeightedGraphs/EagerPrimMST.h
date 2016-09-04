#pragma once
#include "EWGraph.h"
#include <list>
#include "IndexedMinPQ.h"

class EagerPrimMST
{
	void visitVertex(int v);
public:
	typedef std::list<Edge> MSTEdgesContainer;
	EagerPrimMST(const EWGraph& graph);
	MSTEdgesContainer edges();
	double getWeight();
private:
	MSTEdgesContainer MSTEdges;
	double weight;
	const EWGraph& graph;
	IndexedMinPQ<Edge> minPQ;
	std::vector<bool> marked;
};