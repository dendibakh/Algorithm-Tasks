#include "TopologicalSort.h"

namespace TpgSort
{
	void TopologicalSort::dfs(const DiGraph& graph, int v)
	{
		marked[v] = true;
		DiGraph::EdgesList list = graph.getAdjacentVertex(v);
		for (DiGraph::EdgesList::const_iterator i = list.begin(); i != list.end(); ++i)
		{
			if (!marked[*i])
				dfs(graph, *i);
		}
		rPostOrder.push(v);
	}

	TopologicalSort::TopologicalSort(const DiGraph& graph) : graph(graph), marked(graph.getVertexCount(), false)
	{
		for (int i = 0; i < graph.getVertexCount(); ++i)
		{
			if (!marked[i])
				dfs(graph, i);
		}
	}

	TopologicalSort::ReversePostOrderContainer TopologicalSort::getReversePostOrder()
	{
		return rPostOrder;
	}
}