#include "KruskalMST.h"
#include "UnionFind.h"
#include <queue>
#include <functional>

KruskalMST::KruskalMST(const EWGraph& graph) : weight(0.0)
{
	EWGraph::EdgesList edges = graph.getAllEdges();
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> minPQ(edges.begin(), edges.end());
	
	int vertexCount = graph.getVertexCount();
	UnionFind uf(vertexCount);
	while ((MSTEdges.size() < vertexCount - 1) && (!minPQ.empty()))
	{
		Edge curEdge = minPQ.top();
		int v = curEdge.either();
		int w = curEdge.other(v);
		if (!uf.connected(v, w))
		{
			uf.unionElems(v, w);
			MSTEdges.push_back(curEdge);
			weight += curEdge.getWeight();
		}
		minPQ.pop();
	}
}

KruskalMST::MSTEdgesContainer KruskalMST::edges()
{
	return MSTEdges;
}

double KruskalMST::getWeight()
{
	return weight;
}
