#include "stdafx.h"
#include "CppUnitTest.h"
#include "dfs.h"
#include "digraph.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dfs;

namespace DiGraphUnitTest
{
	TEST_CLASS(DiGraphPathClassTests)
	{
	public:

		TEST_METHOD(CheckConstruct)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			Paths<DiGraph> paths(graph, 0);
		}

		TEST_METHOD(CheckWrongConstruct)
		{
			DiGraph graph(3);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);

			try
			{
				Paths<DiGraph> paths(graph, -1);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckHasPathTo)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			Paths<DiGraph> paths(graph, 0);
			Assert::AreEqual(paths.hasPathTo(1), true);
			Assert::AreEqual(paths.hasPathTo(2), true);
			Assert::AreEqual(paths.hasPathTo(3), true);
			Assert::AreEqual(paths.hasPathTo(4), true);
			Assert::AreEqual(paths.hasPathTo(5), true);
			Assert::AreEqual(paths.hasPathTo(6), true);

			Assert::AreEqual(paths.hasPathTo(7), false);
			Assert::AreEqual(paths.hasPathTo(8), false);

			Assert::AreEqual(paths.hasPathTo(9), false);
			Assert::AreEqual(paths.hasPathTo(10), false);
			Assert::AreEqual(paths.hasPathTo(11), false);
			Assert::AreEqual(paths.hasPathTo(12), false);
		}

		TEST_METHOD(CheckHasPathTo2)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			Paths<DiGraph> paths(graph, 11);
			Assert::AreEqual(paths.hasPathTo(1), false);
			Assert::AreEqual(paths.hasPathTo(2), false);
			Assert::AreEqual(paths.hasPathTo(3), false);
			Assert::AreEqual(paths.hasPathTo(4), false);
			Assert::AreEqual(paths.hasPathTo(5), false);
			Assert::AreEqual(paths.hasPathTo(6), false);

			Assert::AreEqual(paths.hasPathTo(7), false);
			Assert::AreEqual(paths.hasPathTo(8), false);

			Assert::AreEqual(paths.hasPathTo(9), false);
			Assert::AreEqual(paths.hasPathTo(10), false);
			Assert::AreEqual(paths.hasPathTo(11), true);
			Assert::AreEqual(paths.hasPathTo(12), true);
		}

		TEST_METHOD(CheckAllReachable1)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			Paths<DiGraph> paths(graph, 9);

			Paths<DiGraph>::AllReachableVertexSet etalonReachable = { 9, 10, 11, 12 };
			Paths<DiGraph>::AllReachableVertexSet actualReachable = paths.getAllReachable();
			std::sort(etalonReachable.begin(), etalonReachable.end());
			std::sort(actualReachable.begin(), actualReachable.end());
			Assert::IsTrue(std::equal(actualReachable.begin(), actualReachable.end(), etalonReachable.begin()));
		}

		TEST_METHOD(CheckAllReachable2)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			Paths<DiGraph> paths(graph, 10);

			Paths<DiGraph>::AllReachableVertexSet etalonReachable = { 10 };
			Paths<DiGraph>::AllReachableVertexSet actualReachable = paths.getAllReachable();
			std::sort(etalonReachable.begin(), etalonReachable.end());
			std::sort(actualReachable.begin(), actualReachable.end());
			Assert::IsTrue(std::equal(actualReachable.begin(), actualReachable.end(), etalonReachable.begin()));
		}

		TEST_METHOD(CheckAllReachable3)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			Paths<DiGraph> paths(graph, 11);

			Paths<DiGraph>::AllReachableVertexSet etalonReachable = { 11, 12 };
			Paths<DiGraph>::AllReachableVertexSet actualReachable = paths.getAllReachable();
			std::sort(etalonReachable.begin(), etalonReachable.end());
			std::sort(actualReachable.begin(), actualReachable.end());
			Assert::IsTrue(std::equal(actualReachable.begin(), actualReachable.end(), etalonReachable.begin()));
		}

		TEST_METHOD(CheckAllReachable4)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			Paths<DiGraph> paths(graph, 0);

			Paths<DiGraph>::AllReachableVertexSet etalonReachable = { 0, 1, 2, 3, 4, 5, 6 };
			Paths<DiGraph>::AllReachableVertexSet actualReachable = paths.getAllReachable();
			std::sort(etalonReachable.begin(), etalonReachable.end());
			std::sort(actualReachable.begin(), actualReachable.end());
			Assert::IsTrue(std::equal(actualReachable.begin(), actualReachable.end(), etalonReachable.begin()));
		}

		TEST_METHOD(CheckAllReachable5)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			Paths<DiGraph> paths(graph, 5);

			Paths<DiGraph>::AllReachableVertexSet etalonReachable = { 3, 4, 5 };
			Paths<DiGraph>::AllReachableVertexSet actualReachable = paths.getAllReachable();
			std::sort(etalonReachable.begin(), etalonReachable.end());
			std::sort(actualReachable.begin(), actualReachable.end());
			Assert::IsTrue(std::equal(actualReachable.begin(), actualReachable.end(), etalonReachable.begin()));
		}

		TEST_METHOD(CheckAllReachableFromSetOfSources1)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			std::vector<int> sources = { 9 };
			Paths<DiGraph> paths(graph, sources);

			Paths<DiGraph>::AllReachableVertexSet etalonReachable = { 9, 10, 11, 12 };
			Paths<DiGraph>::AllReachableVertexSet actualReachable = paths.getAllReachable();
			std::sort(etalonReachable.begin(), etalonReachable.end());
			std::sort(actualReachable.begin(), actualReachable.end());
			Assert::IsTrue(std::equal(actualReachable.begin(), actualReachable.end(), etalonReachable.begin()));
		}

		TEST_METHOD(CheckAllReachableFromSetOfSources2)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			std::vector<int> sources = { 9, 8 };
			Paths<DiGraph> paths(graph, sources);

			Paths<DiGraph>::AllReachableVertexSet etalonReachable = { 8, 9, 10, 11, 12 };
			Paths<DiGraph>::AllReachableVertexSet actualReachable = paths.getAllReachable();
			std::sort(etalonReachable.begin(), etalonReachable.end());
			std::sort(actualReachable.begin(), actualReachable.end());
			Assert::IsTrue(std::equal(actualReachable.begin(), actualReachable.end(), etalonReachable.begin()));
		}

		TEST_METHOD(CheckAllReachableFromSetOfSources3)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			std::vector<int> sources = { 9, 7 };
			Paths<DiGraph> paths(graph, sources);

			Paths<DiGraph>::AllReachableVertexSet etalonReachable = { 7, 8, 9, 10, 11, 12 };
			Paths<DiGraph>::AllReachableVertexSet actualReachable = paths.getAllReachable();
			std::sort(etalonReachable.begin(), etalonReachable.end());
			std::sort(actualReachable.begin(), actualReachable.end());
			Assert::IsTrue(std::equal(actualReachable.begin(), actualReachable.end(), etalonReachable.begin()));
		}

		TEST_METHOD(CheckAllReachableFromSetOfSources4)
		{
			DiGraph graph(13);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 6);
			graph.addEdge(0, 5);
			graph.addEdge(5, 3);
			graph.addEdge(3, 4);
			graph.addEdge(5, 4);
			graph.addEdge(6, 4);

			graph.addEdge(7, 8);

			graph.addEdge(9, 10);
			graph.addEdge(9, 11);
			graph.addEdge(9, 12);
			graph.addEdge(11, 12);

			std::vector<int> sources = { 9, 7, 5 };
			Paths<DiGraph> paths(graph, sources);

			Paths<DiGraph>::AllReachableVertexSet etalonReachable = { 3, 4, 5, 7, 8, 9, 10, 11, 12 };
			Paths<DiGraph>::AllReachableVertexSet actualReachable = paths.getAllReachable();
			std::sort(etalonReachable.begin(), etalonReachable.end());
			std::sort(actualReachable.begin(), actualReachable.end());
			Assert::IsTrue(std::equal(actualReachable.begin(), actualReachable.end(), etalonReachable.begin()));
		}
	};
}