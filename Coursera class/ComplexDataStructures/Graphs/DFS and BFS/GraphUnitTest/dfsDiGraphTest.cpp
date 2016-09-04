#include "stdafx.h"
#include "CppUnitTest.h"
#include "dfs.h"
#include "digraph.h"

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

		bool equalStacks(Paths<DiGraph>::VertexStack lhs, Paths<DiGraph>::VertexStack rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			while (!lhs.empty())
			{
				if (lhs.top() != rhs.top())
					return false;
				lhs.pop();
				rhs.pop();
			}
			return true;
		}

		TEST_METHOD(CheckPathTo)
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

			Paths<DiGraph>::VertexStack etalon6;
			etalon6.push(6);
			etalon6.push(0);
			Paths<DiGraph>::VertexStack expected6 = paths.pathTo(6);
			Assert::IsTrue(equalStacks(etalon6, expected6));

			Paths<DiGraph>::VertexStack etalon3;
			etalon3.push(3);
			etalon3.push(5);
			etalon3.push(0);
			Paths<DiGraph>::VertexStack expected3 = paths.pathTo(3);
			Assert::IsTrue(equalStacks(etalon3, expected3));

			Paths<DiGraph>::VertexStack etalon5;
			etalon5.push(5);
			etalon5.push(0);
			Paths<DiGraph>::VertexStack expected5 = paths.pathTo(5);
			Assert::IsTrue(equalStacks(etalon5, expected5));

			Paths<DiGraph>::VertexStack stack8 = paths.pathTo(8);
			Assert::IsTrue(stack8.empty());

			Paths<DiGraph>::VertexStack stack12 = paths.pathTo(12);
			Assert::IsTrue(stack12.empty());
		}

		TEST_METHOD(CheckPathTo2)
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

			Paths<DiGraph>::VertexStack etalon11;
			etalon11.push(11);
			etalon11.push(9);
			Paths<DiGraph>::VertexStack expected11 = paths.pathTo(11);
			Assert::IsTrue(equalStacks(etalon11, expected11));

			Paths<DiGraph>::VertexStack etalon10;
			etalon10.push(10);
			etalon10.push(9);
			Paths<DiGraph>::VertexStack expected10 = paths.pathTo(10);
			Assert::IsTrue(equalStacks(etalon10, expected10));

			Paths<DiGraph>::VertexStack stack8 = paths.pathTo(8);
			Assert::IsTrue(stack8.empty());

			Paths<DiGraph>::VertexStack stack2 = paths.pathTo(2);
			Assert::IsTrue(stack2.empty());
		}
	};
}