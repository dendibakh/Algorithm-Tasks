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
				{
					dfs(graph, *i);
					edgeTo[*i] = v;
				}
			}
		}
	public:
		typedef std::stack<int> VertexStack;
		Paths(const GraphType& graph, int source) : graph(graph), source(source), marked(graph.getVertexCount(), false), edgeTo(graph.getVertexCount(), -1)
		{
			if ((source < 0) || source >= graph.getVertexCount())
				throw std::runtime_error("Invalid source vertex");
			dfs(graph, source);
		}
		
		bool hasPathTo(int v) const
		{
			return marked[v];
		}

		VertexStack pathTo(int v) const
		{
			VertexStack st;
			if (!hasPathTo(v))
				return st;
			for (int i = v; i != source; i = edgeTo[i])
			{
				st.push(i);
			}
			st.push(source);
			return st;
		}
	private:
		const GraphType& graph;
		const int source;
		std::vector<bool> marked;
		std::vector<int> edgeTo;
	};
}