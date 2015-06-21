#pragma once
#include "EWDiGraph.h"
#include <stack>

class DAG_SP
{
	void relax(const Edge& e);
public:
	typedef std::stack<int> PathToStack;
	DAG_SP(const EWDiGraph& graph, int source);
	double distTo(int v) const;
	PathToStack pathTo(int v) const;
	bool hasPathTo(int v) const;
private:
	std::vector<double> distances;
	std::vector<Edge> edges;
};