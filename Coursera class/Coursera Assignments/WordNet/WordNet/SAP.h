#pragma once
#include <list>
#include "digraph.h"
#include "TopologicalSort.h"

struct CommonAncestor
{
	int lenght;
	int ancestorID;
};

class SAP
{
	void checkVertex(int v) const;
public:
	// constructor takes a digraph (not necessarily a DAG)
	SAP(const DiGraph& graph);

	// find shortest ancestral path between v and w;
	CommonAncestor findClosestAncestor(int v, int w);
	CommonAncestor findClosestAncestorFromTwoLists(const std::list<int>& v, const std::list<int>& w);
private:
	const DiGraph& graph;
	std::list<int> revPostOrder;
};