#include "LazyPrimMST.h"

LazyPrimMST::LazyPrimMST(const EWGraph& graph) : weight(0.0), graph(graph), marked(graph.getVertexCount(), false)
{
	visitVertex(0);
	
	while (!minPQ.empty())
	{
		Edge curEdge = minPQ.top();
		minPQ.pop();
		int v = curEdge.either();
		int w = curEdge.other(v);
		if (!marked[v] || !marked[w])
		{
			MSTEdges.push_back(curEdge);
			weight += curEdge.getWeight();
			if (!marked[v])
				visitVertex(v);
			if (!marked[w])
				visitVertex(w);
		}		
	}
}

void LazyPrimMST::visitVertex(int v)
{
	marked[v] = true;
	EWGraph::EdgesList adjacent = graph.getAdjacentVertex(v);
	for (auto i = adjacent.begin(); i != adjacent.end(); ++i)
	{
		int w = i->other(v);
		if (!marked[w])
			minPQ.push(*i);
	}
}

LazyPrimMST::MSTEdgesContainer LazyPrimMST::edges()
{
	return MSTEdges;
}

double LazyPrimMST::getWeight()
{
	return weight;
}