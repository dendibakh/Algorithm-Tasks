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
			DiGraph graph(7);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 5);
			graph.addEdge(5, 2);
			graph.addEdge(6, 0);
			graph.addEdge(3, 2);
			graph.addEdge(3, 5);
			graph.addEdge(3, 6);
			graph.addEdge(3, 4);
			graph.addEdge(6, 4);
			graph.addEdge(1, 4);

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
			DiGraph graph(7);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 5);
			graph.addEdge(5, 2);
			graph.addEdge(6, 0);
			graph.addEdge(3, 2);
			graph.addEdge(3, 5);
			graph.addEdge(3, 6);
			graph.addEdge(3, 4);
			graph.addEdge(6, 4);
			graph.addEdge(1, 4);

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
			DiGraph graph(7);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 5);
			graph.addEdge(5, 2);
			graph.addEdge(6, 0);
			graph.addEdge(2, 3);
			graph.addEdge(3, 5);
			graph.addEdge(3, 6);
			graph.addEdge(3, 4);
			graph.addEdge(6, 4);
			graph.addEdge(1, 4);

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