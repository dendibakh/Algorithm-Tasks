#include "stdafx.h"
#include "CppUnitTest.h"
#include "EWDiGraph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EWGraphUnitTest
{
	TEST_CLASS(EWDiGraphUnitTest)
	{
	public:

		TEST_METHOD(CheckConstruct)
		{
			EWDiGraph graph(10);
		}

		TEST_METHOD(CheckConstructInWork)
		{
			EWDiGraph graph(2);
			Assert::AreEqual(graph.getVertexCount(), 2);
			EWDiGraph::EdgesList list = graph.getAdjacentVertex(1);
			Assert::IsTrue(list.empty());
		}

		TEST_METHOD(CheckAddEdge)
		{
			EWDiGraph graph(2);
			graph.addEdge(Edge(0, 1, 0.22));
			EWDiGraph::EdgesList list0 = graph.getAdjacentVertex(0);
			Assert::AreEqual(int(list0.size()), 1);
			int v = list0.front().from();
			int w = list0.front().to();
			Assert::AreEqual(v, 0);
			Assert::AreEqual(w, 1);
			Assert::AreEqual(list0.front().getWeight(), 0.22);

			EWDiGraph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(list1.empty());
		}

		TEST_METHOD(CheckAddWrongEdge)
		{
			EWDiGraph graph(2);
			try
			{
				graph.addEdge(Edge(0, 3, 0.44));
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckAddMoreEdge)
		{
			EWDiGraph graph(5);
			graph.addEdge(Edge(0, 1, 0.5));
			graph.addEdge(Edge(0, 2, 0.5));
			graph.addEdge(Edge(1, 2, 0.5));
			graph.addEdge(Edge(2, 3, 0.5));
			graph.addEdge(Edge(3, 4, 0.5));
			graph.addEdge(Edge(2, 4, 0.5));

			EWDiGraph::EdgesList expected1;
			expected1.push_front(Edge(1, 2, 0.5));
			EWDiGraph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(std::equal(list1.begin(), list1.end(), expected1.begin()));

			EWDiGraph::EdgesList expected2;
			expected2.push_front(Edge(2, 4, 0.5));
			expected2.push_front(Edge(2, 3, 0.5));
			EWDiGraph::EdgesList list2 = graph.getAdjacentVertex(2);
			Assert::IsTrue(std::equal(list2.begin(), list2.end(), expected2.begin()));

			EWDiGraph::EdgesList list4 = graph.getAdjacentVertex(4);
			Assert::IsTrue(list4.empty());
		}

		TEST_METHOD(CheckGetWrongAdjacentVertex)
		{
			EWDiGraph graph(5);
			graph.addEdge(Edge(0, 1, 0.5));
			graph.addEdge(Edge(0, 4, 0.5));

			try
			{
				EWDiGraph::EdgesList list10 = graph.getAdjacentVertex(10);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckCounts)
		{
			EWDiGraph graph(5);
			graph.addEdge(Edge(0, 1, 0.5));
			graph.addEdge(Edge(0, 2, 0.5));
			graph.addEdge(Edge(1, 2, 0.5));
			graph.addEdge(Edge(2, 3, 0.5));
			graph.addEdge(Edge(3, 4, 0.5));
			graph.addEdge(Edge(2, 4, 0.5));

			Assert::AreEqual(graph.getEdgesCount(), 6);
			Assert::AreEqual(graph.getVertexCount(), 5);
		}

		TEST_METHOD(CheckCounts2)
		{
			EWDiGraph graph(5);
			graph.addEdge(Edge(0, 1, 0.5));
			graph.addEdge(Edge(0, 2, 0.5));
			graph.addEdge(Edge(0, 2, 0.5));
			graph.addEdge(Edge(1, 2, 0.5));
			graph.addEdge(Edge(2, 3, 0.5));
			graph.addEdge(Edge(3, 4, 0.5));
			graph.addEdge(Edge(3, 4, 0.5));
			graph.addEdge(Edge(2, 4, 0.5));

			Assert::AreEqual(graph.getEdgesCount(), 6);
			Assert::AreEqual(graph.getVertexCount(), 5);
		}

		TEST_METHOD(ChecktoString)
		{
			EWDiGraph graph(5);
			graph.addEdge(Edge(0, 1, 0.5));
			graph.addEdge(Edge(0, 2, 0.5));
			graph.addEdge(Edge(1, 2, 0.5));
			graph.addEdge(Edge(2, 3, 0.5));
			graph.addEdge(Edge(3, 4, 0.5));
			graph.addEdge(Edge(2, 4, 0.5));

			Assert::IsTrue(graph.toString() == std::string("0 - 1 0.5\n0 - 2 0.5\n1 - 2 0.5\n2 - 3 0.5\n2 - 4 0.5\n3 - 4 0.5\n"));
		}
	};
}