#pragma once

#include "FlowNetwork.h"

class FordFulkerson
{
	bool hasAugumentingPath(int s, int t);
	void dfs(int v);
public:
	FordFulkerson(const FlowNetwork& flowNet, int s, int t);
	int getMaxFlow();
	typedef std::list<int> MinCutVertecies;
	MinCutVertecies getMinCutVertecies();
private:
	FlowNetwork fNet;
	std::vector<bool> marked;
	std::vector<FlowEdge> edgeTo;
	int MaxFlow;
	MinCutVertecies minCut;
};