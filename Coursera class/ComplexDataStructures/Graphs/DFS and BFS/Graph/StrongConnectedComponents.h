#pragma once
#include <stack>
#include <vector>
#include "digraph.h"

namespace StrConComp
{
	class StrongConnectedComponents
	{
		void dfs(int v, int curID);
		void fillComponentsContainer();
	public:
		typedef std::vector< std::vector<int> > ComponentsContainer;
		StrongConnectedComponents(const DiGraph& graph);
		int getComponentsCount();
		bool isAnyCycles();
		ComponentsContainer getComponents();
	private:
		std::vector<int> ids; 
		const DiGraph reversedGraph;
		ComponentsContainer compContainer;
	};
}