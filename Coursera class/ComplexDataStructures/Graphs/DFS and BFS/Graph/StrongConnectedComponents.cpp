#include "StrongConnectedComponents.h"
#include "TopologicalSort.h"

using namespace TpgSort;

static const int nullValue = -1;

namespace StrConComp
{
	StrongConnectedComponents::StrongConnectedComponents(const DiGraph& graph) : reversedGraph(graph.getReversed()), ids(graph.getVertexCount(), nullValue)
	{
		TopologicalSort tpgSort(reversedGraph);
		TopologicalSort::ReversePostOrderContainer revPostOrder = tpgSort.getReversePostOrder();
		int curID = 0;
		while (!revPostOrder.empty())
		{
			int curVertex = revPostOrder.front();
			if (nullValue == ids[curVertex])
			{
				dfs(curVertex, curID);
				++curID;
			}
			
			revPostOrder.pop();
		}
		fillComponentsContainer();
	}

	void StrongConnectedComponents::dfs(int v, int curID)
	{
		ids[v] = curID;
		DiGraph::EdgesList list = reversedGraph.getAdjacentVertex(v);
		for (DiGraph::EdgesList::const_iterator i = list.begin(); i != list.end(); ++i)
		{
			if (nullValue == ids[*i])
				dfs(*i, curID);
		}
	}

	void StrongConnectedComponents::fillComponentsContainer()
	{
		int compCount = getComponentsCount();
		compContainer.resize(compCount);
		for (int i = 0; i < reversedGraph.getVertexCount(); ++i)
		{
			compContainer[ids[i]].push_back(i);
		}
	}

	int StrongConnectedComponents::getComponentsCount()
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

	bool StrongConnectedComponents::isAnyCycles()
	{
		return ids.size() > this->getComponentsCount();
	}

	StrongConnectedComponents::ComponentsContainer StrongConnectedComponents::getComponents()
	{
		return compContainer;
	}
}