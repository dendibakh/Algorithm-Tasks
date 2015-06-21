#include "LongestPath.h"

LongestPath::LongestPath(const EWDiGraph& graph, int source) : DSP(graph.getNegated(), source)
{
	
}

double LongestPath::distTo(int v) const
{
	return -DSP.distTo(v);
}

LongestPath::PathToStack LongestPath::pathTo(int v) const
{
	return DSP.pathTo(v);
}

bool LongestPath::hasPathTo(int v) const
{
	return DSP.hasPathTo(v);
}