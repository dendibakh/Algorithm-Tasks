#pragma once
#include <queue>
#include <vector>
#include "digraph.h"

namespace TpgSort
{
	class TopologicalSort
	{
		void dfs(const DiGraph& graph, int v);
	public:
		typedef std::queue<int> ReversePostOrderContainer;
		TopologicalSort(const DiGraph& graph);
		ReversePostOrderContainer getReversePostOrder();
	private:
		const DiGraph& graph;
		std::vector<bool> marked;
		ReversePostOrderContainer rPostOrder;
	};
}