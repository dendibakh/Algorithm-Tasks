#include "stdafx.h"
#include "digraph.h"
#include "util.h"
#include <functional>

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace DiGraphUnitTest
{
	[TestClass]
	public ref class DiGraphClassTests
	{
	public:
		[TestMethod]
		void CheckConstruct()
		{
			DiGraph graph(10);
		}

		[TestMethod]
		void CheckConstructInWork()
		{
			DiGraph graph(2);
			Assert::AreEqual(graph.getVertexCount(), 2);
			DiGraph::EdgesList list = graph.getAdjacentVertex(1);
			Assert::IsTrue(list.empty());
		}

		[TestMethod]
		void CheckAddEdge()
		{
			DiGraph graph(2);
			graph.addEdge(0, 1);
			DiGraph::EdgesList list0 = graph.getAdjacentVertex(0);
			Assert::AreEqual(int(list0.size()), 1);
			Assert::AreEqual(list0.front(), 1);
			DiGraph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(list1.empty());
		}

		[TestMethod]
		void CheckAddWrongEdge()
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

		[TestMethod]
		void CheckAddMoreEdge()
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

		[TestMethod]
		void CheckGetWrongAdjacentVertex()
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

		[TestMethod]
		void CheckCounts()
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

		[TestMethod]
		void CheckCounts2()
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

		[TestMethod]
		void ChecktoString()
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

		[TestMethod]
		void CheckDegree()
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

		[TestMethod]
		void CheckWrongDegree()
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

		[TestMethod]
		void CheckMaxDegree()
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

		[TestMethod]
		void CheckAverageDegree()
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

		[TestMethod]
		void CheckNumberOfSelfLoops()
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

		[TestMethod]
		void CheckNumberOfSelfLoops2()
		{
			DiGraph graph(5);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(1, 2);
			graph.addEdge(0, 0);
			graph.addEdge(2, 2);

			Assert::AreEqual(graph.numberOfSelfLoops(), 2);
		}

		[TestMethod]
		void CheckGetDiGraphFromFile()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph1);

			int arr1[] = { 0 };
			DiGraph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(std::equal(list1.begin(), list1.end(), arr1));

			int arr10[] = { 5 };
			DiGraph::EdgesList list10 = graph.getAdjacentVertex(10);
			Assert::IsTrue(std::equal(list10.begin(), list10.end(), arr10));

			DiGraph::EdgesList list0 = graph.getAdjacentVertex(0);
			Assert::IsTrue(list0.empty());
		}

		[TestMethod]
		void CheckGetDiGraphFromFile2()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph2);

			int arr1[] = { 0, 2 };
			DiGraph::EdgesList list1 = graph.getAdjacentVertex(1);
			Assert::IsTrue(std::equal(list1.begin(), list1.end(), arr1));

			int arr4[] = { 5 };
			DiGraph::EdgesList list4 = graph.getAdjacentVertex(4);
			Assert::IsTrue(std::equal(list4.begin(), list4.end(), arr4));

			DiGraph::EdgesList list0 = graph.getAdjacentVertex(0);
			Assert::IsTrue(list0.empty());
		}
	};
}