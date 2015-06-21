#pragma once
#include <queue>
#include <stack>
#include <vector>
#include "EWDiGraph.h"

namespace TpgSort
{
	class TopologicalSort
	{
		void dfs(const EWDiGraph& graph, int v);
	public:
		typedef std::queue<int> ReversePostOrderContainer;
		typedef std::stack<int> PostOrderContainer;
		TopologicalSort(const EWDiGraph& graph);
		ReversePostOrderContainer getReversePostOrder();
		PostOrderContainer getPostOrder();
	private:
		const EWDiGraph& graph;
		std::vector<bool> marked;
		ReversePostOrderContainer rPostOrder;
		PostOrderContainer PostOrder;
	};
}