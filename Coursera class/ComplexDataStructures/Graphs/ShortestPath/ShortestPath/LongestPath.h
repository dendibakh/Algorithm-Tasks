#pragma once
#include "DijkstraSP.h"

class LongestPath
{
public:
	typedef std::stack<int> PathToStack;
	LongestPath(const EWDiGraph& graph, int source);
	double distTo(int v) const;
	PathToStack pathTo(int v) const;
	bool hasPathTo(int v) const;
private:
	const DijkstraSP DSP;
};