#pragma once
#include "EWDiGraph.h"
#include "IndexedMinPQ.h"
#include <list>

class DijkstraSP
{
	void relax(IndexedMinPQ<double>& minPQ, const Edge& e);
public:
	typedef std::list<int> PathToStack;
	DijkstraSP(const EWDiGraph& graph, int source);
	double distTo(int v) const;
	PathToStack pathTo(int v) const;
	bool hasPathTo(int v) const;
private:
	std::vector<double> distances;
	std::vector<Edge> edges;
	const int source;
};