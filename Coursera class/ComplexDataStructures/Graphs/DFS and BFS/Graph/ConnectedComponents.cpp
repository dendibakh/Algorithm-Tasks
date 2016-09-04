#include "ConectedComponents.h"
#include <algorithm>

static const int nullValue = -1;

namespace cc
{
	ConnectedComponents::ConnectedComponents(const Graph& graph) : graph(graph), ids(graph.getVertexCount(), nullValue)
	{
		int curID = 0;
		for (int i = 0; i < graph.getVertexCount(); ++i)
		{
			if (nullValue == ids[i])
			{
				dfs(i, curID);
				++curID;
			}
		}
	}

	void ConnectedComponents::dfs(int v, int curID)
	{
		ids[v] = curID;
		Graph::EdgesList list = graph.getAdjacentVertex(v);
		for (Graph::EdgesList::const_iterator i = list.begin(); i != list.end(); ++i)
		{
			if (nullValue == ids[*i])
				dfs(*i, curID);
		}
	}

	bool ConnectedComponents::connected(int v, int w)
	{
		return id(v) == id(w);
	}

	int ConnectedComponents::id(int v)
	{
		return ids[v];
	}

	int ConnectedComponents::count()
	{
		if (ids.empty())
			return 0;
		int retVal = 0;
		for (auto i = ids.begin(); i != ids.end(); ++i)
		{
			retVal = std::max(retVal, *i);
		}
		return retVal + 1;
	}
}