#include "stdafx.h"
#include "CppUnitTest.h"
#include "digraph.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DiGraphUnitTest
{
	TEST_CLASS(DiGraphClassTests)
	{
	public:

		TEST_METHOD(CheckConstruct)
		{
			DiGraph graph(10);
		}

		TEST_METHOD(CheckConstructInWork)
		{
			DiGraph graph(2);
			Assert::AreEqual(graph.getVertexCount(), 2);
			DiGraph::EdgesList list = graph.getAdjacentVertex(1);
			Assert::IsTrue(list.empty());
		}

		TEST_METHOD(CheckAddEdge)
		{
			DiGraph graph(2);
			graph.addEdge(0, 1);
			DiGraph::EdgesList list0 = graph.getAdjacentVertex(0);
			Assert::AreEqual(int(list0.size()), 1);
			Assert::AreEqual(list0.front(), 1);
			DiGraph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(list1.empty());
		}

		TEST_METHOD(CheckAddWrongEdge)
		{
			DiGraph graph(2);
			try
			{
				graph.addEdge(0, 3);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckAddMoreEdge)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			int arr1[] = { 2 };
			DiGraph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(std::equal(list1.begin(), list1.end(), arr1));

			int arr2[] = { 3, 4 };
			DiGraph::EdgesList list2 = graph.getAdjacentVertex(2);
			Assert::IsTrue(std::equal(list2.begin(), list2.end(), arr2));

			DiGraph::EdgesList list4 = graph.getAdjacentVertex(4);
			Assert::IsTrue(list4.empty());
		}

		TEST_METHOD(CheckGetWrongAdjacentVertex)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 4);

			int arr1[] = { 0, 4 };
			DiGraph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(std::equal(list1.begin(), list1.end(), arr1));

			try
			{
				DiGraph::EdgesList list10 = graph.getAdjacentVertex(10);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckCounts)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::AreEqual(graph.getEdgesCount(), 6);
			Assert::AreEqual(graph.getVertexCount(), 5);
		}

		TEST_METHOD(CheckCounts2)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::AreEqual(graph.getEdgesCount(), 6);
			Assert::AreEqual(graph.getVertexCount(), 5);
		}

		TEST_METHOD(ChecktoString)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::IsTrue(graph.toString() == std::string("0 -> 1\n0 -> 2\n1 -> 2\n2 -> 3\n2 -> 4\n3 -> 4\n"));
		}

		TEST_METHOD(CheckDegree)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::AreEqual(graph.degree(0), 2);
			Assert::AreEqual(graph.degree(1), 1);
			Assert::AreEqual(graph.degree(2), 2);
			Assert::AreEqual(graph.degree(3), 1);
			Assert::AreEqual(graph.degree(4), 0);
		}

		TEST_METHOD(CheckWrongDegree)
		{
			DiGraph graph(3);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);

			try
			{
				Assert::AreEqual(graph.degree(-5), 0);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckMaxDegree)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::AreEqual(graph.maxdegree(), 2);
		}

		TEST_METHOD(CheckAverageDegree)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::AreEqual(graph.averagedegree(), 1.2);
		}

		TEST_METHOD(CheckNumberOfSelfLoops)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::AreEqual(graph.numberOfSelfLoops(), 0);
		}

		TEST_METHOD(CheckNumberOfSelfLoops2)
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(0, 0);
			graph.addEdge(2, 2);

			Assert::AreEqual(graph.numberOfSelfLoops(), 2);
		}

		TEST_METHOD(CheckGetReversed)
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

			DiGraph revGraph = graph.getReversed();

			int arr0[] = { 6 };
			DiGraph::EdgesList list0 = revGraph.getAdjacentVertex(0);
			Assert::IsTrue(std::equal(list0.begin(), list0.end(), arr0));

			int arr1[] = { 0 };
			DiGraph::EdgesList list1 = revGraph.getAdjacentVertex(1);
			Assert::IsTrue(std::equal(list1.begin(), list1.end(), arr1));

			int arr2[] = { 0, 3, 5 };
			DiGraph::EdgesList list2 = revGraph.getAdjacentVertex(2);
			Assert::IsTrue(std::equal(list2.begin(), list2.end(), arr2));

			DiGraph::EdgesList list3 = revGraph.getAdjacentVertex(3);
			Assert::IsTrue(list3.empty());

			int arr4[] = { 1, 3, 6 };
			DiGraph::EdgesList list4 = revGraph.getAdjacentVertex(4);
			Assert::IsTrue(std::equal(list4.begin(), list4.end(), arr4));

			int arr5[] = { 0, 3 };
			DiGraph::EdgesList list5 = revGraph.getAdjacentVertex(5);
			Assert::IsTrue(std::equal(list5.begin(), list5.end(), arr5));

			int arr6[] = { 3 };
			DiGraph::EdgesList list6 = revGraph.getAdjacentVertex(6);
			Assert::IsTrue(std::equal(list6.begin(), list6.end(), arr6));
		}

		TEST_METHOD(CheckOperatorEqual1)
		{
			DiGraph graph1(7);
			graph1.addEdge(0, 1);
			graph1.addEdge(0, 2);
			graph1.addEdge(0, 5);

			DiGraph graph2(7);
			graph2.addEdge(0, 1);
			graph2.addEdge(0, 2);
			graph2.addEdge(0, 5);

			Assert::IsTrue(graph1 == graph2);
		}

		TEST_METHOD(CheckOperatorEqual2)
		{
			DiGraph graph1(7);
			graph1.addEdge(0, 1);
			graph1.addEdge(0, 2);
			graph1.addEdge(0, 5);
			graph1.addEdge(5, 2);
			graph1.addEdge(6, 0);
			graph1.addEdge(3, 2);
			graph1.addEdge(3, 5);
			graph1.addEdge(3, 6);
			graph1.addEdge(3, 4);
			graph1.addEdge(6, 4);
			graph1.addEdge(1, 4);

			DiGraph graph2(7);
			graph2.addEdge(0, 1);
			graph2.addEdge(0, 2);
			graph2.addEdge(0, 5);
			graph2.addEdge(5, 2);
			graph2.addEdge(6, 0);
			graph2.addEdge(3, 2);
			graph2.addEdge(3, 5);
			graph2.addEdge(3, 6);
			graph2.addEdge(3, 4);
			graph2.addEdge(6, 4);
			graph2.addEdge(1, 4);

			Assert::IsTrue(graph1 == graph2);
		}

		TEST_METHOD(CheckOperatorEqual3)
		{
			DiGraph graph1(7);

			DiGraph graph2(7);
			
			Assert::IsTrue(graph1 == graph2);
		}

		TEST_METHOD(CheckOperatorEqual4)
		{
			DiGraph graph1(7);

			DiGraph graph2(6);

			Assert::IsFalse(graph1 == graph2);
		}

		TEST_METHOD(CheckOperatorEqual5)
		{
			DiGraph graph1(7);
			graph1.addEdge(0, 1);
			graph1.addEdge(0, 2);
			graph1.addEdge(0, 5);
			graph1.addEdge(5, 2);
			graph1.addEdge(6, 0);

			graph1.addEdge(3, 2);

			graph1.addEdge(3, 5);
			graph1.addEdge(3, 6);
			graph1.addEdge(3, 4);
			graph1.addEdge(6, 4);
			graph1.addEdge(1, 4);

			DiGraph graph2(7);
			graph2.addEdge(0, 1);
			graph2.addEdge(0, 2);
			graph2.addEdge(0, 5);
			graph2.addEdge(5, 2);
			graph2.addEdge(6, 0);

			graph2.addEdge(2, 2);

			graph2.addEdge(3, 5);
			graph2.addEdge(3, 6);
			graph2.addEdge(3, 4);
			graph2.addEdge(6, 4);
			graph2.addEdge(1, 4);

			Assert::IsFalse(graph1 == graph2);
		}

		TEST_METHOD(CheckOperatorEqual6)
		{
			DiGraph graph1(7);
			graph1.addEdge(0, 1);
			graph1.addEdge(0, 2);
			graph1.addEdge(0, 5);

			DiGraph graph2(7);
			graph2.addEdge(0, 1);
			graph2.addEdge(0, 2);
			graph2.addEdge(0, 5);
			graph2.addEdge(0, 6);

			Assert::IsFalse(graph1 == graph2);
		}

		TEST_METHOD(CheckOperatorEqual7)
		{
			DiGraph graph1(7);
			graph1.addEdge(0, 1);
			graph1.addEdge(0, 2);
			graph1.addEdge(0, 5);
			graph1.addEdge(3, 6);
			graph1.addEdge(3, 4);
			graph1.addEdge(3, 5);

			DiGraph graph2(7);
			graph2.addEdge(0, 1);
			graph2.addEdge(0, 2);
			graph2.addEdge(0, 5);
			graph2.addEdge(0, 6);
			graph2.addEdge(3, 6);
			graph2.addEdge(3, 4);

			Assert::IsFalse(graph1 == graph2);
		}

		TEST_METHOD(CheckOperatorEqual8_OrderMakesNoSense)
		{
			DiGraph graph1(7);
			graph1.addEdge(0, 1);
			graph1.addEdge(0, 2);
			graph1.addEdge(0, 5);
			graph1.addEdge(5, 2);
			graph1.addEdge(6, 0);
			graph1.addEdge(3, 2);
			graph1.addEdge(3, 5);
			graph1.addEdge(3, 6);
			graph1.addEdge(3, 4);
			graph1.addEdge(6, 4);
			graph1.addEdge(1, 4);

			DiGraph graph2(7);
			graph2.addEdge(0, 5);
			graph2.addEdge(0, 2);
			graph2.addEdge(0, 1);
			graph2.addEdge(5, 2);
			graph2.addEdge(6, 0);
			graph2.addEdge(3, 5);
			graph2.addEdge(3, 4);
			graph2.addEdge(3, 6);
			graph2.addEdge(3, 2);
			graph2.addEdge(6, 4);
			graph2.addEdge(1, 4);

			Assert::IsTrue(graph1 == graph2);
		}
	};
}