#pragma once
#include "EWGraph.h"
#include <list>

class KruskalMST
{
public:
	typedef std::list<Edge> MSTEdgesContainer;
	KruskalMST(const EWGraph& graph);
	MSTEdgesContainer edges();
	double getWeight();
private:
	MSTEdgesContainer MSTEdges;
	double weight;
};