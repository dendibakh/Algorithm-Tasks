#include "stdafx.h"
#include "CppUnitTest.h"
#include "TopologicalSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TpgSort;

namespace GraphUnitTest
{
	TEST_CLASS(TopologicalSortTest)
	{
	public:

		TEST_METHOD(CheckConstruct)
		{
			EWDiGraph graph(7);
			graph.addEdge(Edge(0, 1, 0.0));
			graph.addEdge(Edge(0, 2, 0.0));
			graph.addEdge(Edge(0, 5, 0.0));
			graph.addEdge(Edge(5, 2, 0.0));
			graph.addEdge(Edge(6, 0, 0.0));
			graph.addEdge(Edge(3, 2, 0.0));
			graph.addEdge(Edge(3, 5, 0.0));
			graph.addEdge(Edge(3, 6, 0.0));
			graph.addEdge(Edge(3, 4, 0.0));
			graph.addEdge(Edge(6, 4, 0.0));
			graph.addEdge(Edge(1, 4, 0.0));

			TopologicalSort tpgSort(graph);
		}

		bool equalStacks(TopologicalSort::ReversePostOrderContainer lhs, TopologicalSort::ReversePostOrderContainer rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			while (!lhs.empty())
			{
				if (lhs.front() != rhs.front())
					return false;
				lhs.pop();
				rhs.pop();
			}
			return true;
		}

		TEST_METHOD(CheckOrder)
		{
			EWDiGraph graph(7);
			graph.addEdge(Edge(0, 1, 0.0));
			graph.addEdge(Edge(0, 2, 0.0));
			graph.addEdge(Edge(0, 5, 0.0));
			graph.addEdge(Edge(5, 2, 0.0));
			graph.addEdge(Edge(6, 0, 0.0));
			graph.addEdge(Edge(3, 2, 0.0));
			graph.addEdge(Edge(3, 5, 0.0));
			graph.addEdge(Edge(3, 6, 0.0));
			graph.addEdge(Edge(3, 4, 0.0));
			graph.addEdge(Edge(6, 4, 0.0));
			graph.addEdge(Edge(1, 4, 0.0));

			TopologicalSort tpgSort(graph);
			TopologicalSort::ReversePostOrderContainer etalon;
			etalon.push(4);
			etalon.push(1);
			etalon.push(2);
			etalon.push(5);
			etalon.push(0);
			etalon.push(6);
			etalon.push(3);
			TopologicalSort::ReversePostOrderContainer expected = tpgSort.getReversePostOrder();
			Assert::IsTrue(equalStacks(etalon, expected));
		}

		TEST_METHOD(CheckOrderWithCycle)
		{
			EWDiGraph graph(7);
			graph.addEdge(Edge(0, 1, 0.0));
			graph.addEdge(Edge(0, 2, 0.0));
			graph.addEdge(Edge(0, 5, 0.0));
			graph.addEdge(Edge(5, 2, 0.0));
			graph.addEdge(Edge(6, 0, 0.0));
			graph.addEdge(Edge(2, 3, 0.0));
			graph.addEdge(Edge(3, 5, 0.0));
			graph.addEdge(Edge(3, 6, 0.0));
			graph.addEdge(Edge(3, 4, 0.0));
			graph.addEdge(Edge(6, 4, 0.0));
			graph.addEdge(Edge(1, 4, 0.0));

			TopologicalSort tpgSort(graph);
			TopologicalSort::ReversePostOrderContainer etalon;
			etalon.push(4);
			etalon.push(1);
			etalon.push(5);
			etalon.push(6);
			etalon.push(3);
			etalon.push(2);
			etalon.push(0);
			TopologicalSort::ReversePostOrderContainer expected = tpgSort.getReversePostOrder();
			Assert::IsTrue(equalStacks(etalon, expected));
		}
	};
}