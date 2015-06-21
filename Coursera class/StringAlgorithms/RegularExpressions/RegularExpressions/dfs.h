#pragma once
#include <stack>
#include <vector>

// DFS works both for undirected and directed graphs
namespace dfs
{
	template <class GraphType>
	class Paths
	{
		void dfs(const GraphType& graph, int v)
		{
			marked[v] = true;
			GraphType::EdgesList list = graph.getAdjacentVertex(v);
			for (GraphType::EdgesList::const_iterator i = list.begin(); i != list.end(); ++i)
			{
				if (!marked[*i])
					dfs(graph, *i);
			}
		}
	public:
		typedef std::stack<int> VertexStack;
		typedef std::vector<int> AllReachableVertexSet;
		Paths(const GraphType& graph, int source) : graph(graph), marked(graph.getVertexCount(), false)
		{
			if ((source < 0) || source >= graph.getVertexCount())
				throw std::runtime_error("Invalid source vertex");
			dfs(graph, source);
		}

		Paths(const GraphType& graph, const std::vector<int>& sources) : graph(graph), marked(graph.getVertexCount(), false)
		{
			for (std::vector<int>::const_iterator iter = sources.begin(); iter != sources.end(); ++iter)
			{
				if ((*iter < 0) || *iter >= graph.getVertexCount())
					throw std::runtime_error("Invalid source vertex");
				dfs(graph, *iter);
			}
		}
		
		bool hasPathTo(int v) const
		{
			return marked[v];
		}

		AllReachableVertexSet getAllReachable()
		{
			AllReachableVertexSet reachableVertecies;
			int N = graph.getVertexCount();
			for (int i = 0; i < N; ++i)
			{
				if (hasPathTo(i))
					reachableVertecies.push_back(i);
			}
			return reachableVertecies;
		}
	private:
		const GraphType& graph;
		std::vector<bool> marked;
	};
}