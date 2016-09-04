#include "EagerPrimMST.h"

EagerPrimMST::EagerPrimMST(const EWGraph& graph) : weight(0.0), graph(graph), marked(graph.getVertexCount(), false), minPQ(graph.getVertexCount())
{
	visitVertex(0);

	while (!minPQ.isEmpty())
	{
		Edge curEdge = minPQ.minKey();
		minPQ.delMin();
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

void EagerPrimMST::visitVertex(int v)
{
	marked[v] = true;
	EWGraph::EdgesList adjacent = graph.getAdjacentVertex(v);
	for (auto i = adjacent.begin(); i != adjacent.end(); ++i)
	{
		int w = i->other(v);
		if (!marked[w])
		{
			if (minPQ.contains(w))
			{
				Edge alreadyFoundEdge = minPQ.keyOf(w);
				if (*i < alreadyFoundEdge)
					minPQ.decreaseKey(w, *i);
			}
			else
			{
				minPQ.insert(w, *i);
			}
		}
	}
}

EagerPrimMST::MSTEdgesContainer EagerPrimMST::edges()
{
	return MSTEdges;
}

double EagerPrimMST::getWeight()
{
	return weight;
}