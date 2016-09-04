#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphUnitTest
{		
	TEST_CLASS(GraphClassTests)
	{
	public:
		
		TEST_METHOD(CheckConstruct)
		{
			Graph graph(10);
		}

		TEST_METHOD(CheckConstructInWork)
		{
			Graph graph(2);
			Assert::AreEqual(graph.getVertexCount(), 2);
			Graph::EdgesList list = graph.getAdjacentVertex(1);
			Assert::IsTrue(list.empty());
		}

		TEST_METHOD(CheckAddEdge)
		{
			Graph graph(2);
			graph.addEdge(0, 1);
			Graph::EdgesList list0 = graph.getAdjacentVertex(0);
			Assert::AreEqual(int(list0.size()), 1);
			Assert::AreEqual(list0.front(), 1);
			Graph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::AreEqual(int(list1.size()), 1);
			Assert::AreEqual(list1.front(), 0);
		}

		TEST_METHOD(CheckAddWrongEdge)
		{
			Graph graph(2);
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
			Graph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);
			
			int arr1[] = { 0, 2 };
			Graph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(std::equal(list1.begin(), list1.end(), arr1 ));

			int arr2[] = { 0, 1, 3, 4 };
			Graph::EdgesList list2 = graph.getAdjacentVertex(2);
			Assert::IsTrue(std::equal(list2.begin(), list2.end(), arr2));

			int arr4[] = { 3, 2 }; 
			Graph::EdgesList list4 = graph.getAdjacentVertex(4);
			Assert::IsTrue(std::equal(list4.begin(), list4.end(), arr4));
		}

		TEST_METHOD(CheckGetWrongAdjacentVertex)
		{
			Graph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 4);
			
			int arr1[] = { 0, 4 };
			Graph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(std::equal(list1.begin(), list1.end(), arr1));

			try
			{
				Graph::EdgesList list10 = graph.getAdjacentVertex(10);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckCounts)
		{
			Graph graph(5);
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
			Graph graph(5);
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
			Graph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::IsTrue(graph.toString() == std::string("0 - 1\n0 - 2\n1 - 2\n2 - 3\n2 - 4\n3 - 4\n"));
		}
		
		TEST_METHOD(CheckDegree)
		{
			Graph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::AreEqual(graph.degree(0), 2);
			Assert::AreEqual(graph.degree(1), 2);
			Assert::AreEqual(graph.degree(2), 4);
			Assert::AreEqual(graph.degree(3), 2);
			Assert::AreEqual(graph.degree(4), 2);
		}

		TEST_METHOD(CheckWrongDegree)
		{
			Graph graph(3);
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
			Graph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::AreEqual(graph.maxdegree(), 4);
		}

		TEST_METHOD(CheckAverageDegree)
		{
			Graph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(2, 3);
			graph.addEdge(3, 4);
			graph.addEdge(2, 4);

			Assert::AreEqual(graph.averagedegree(), 2.4);
		}

		TEST_METHOD(CheckNumberOfSelfLoops)
		{
			Graph graph(5);
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
			Graph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(0, 0);
			graph.addEdge(2, 2);
		
			Assert::AreEqual(graph.numberOfSelfLoops(), 2);
		}
	};
}	