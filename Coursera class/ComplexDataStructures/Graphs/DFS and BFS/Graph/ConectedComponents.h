#pragma once
#include "Graph.h"

namespace cc
{
	class ConnectedComponents
	{
		void dfs(int v, int curID);
	public:
		ConnectedComponents(const Graph& graph);
		bool connected(int v, int w);
		int count();
		int id(int v);
	private:
		const Graph& graph;
		std::vector<int> ids;
	};
}