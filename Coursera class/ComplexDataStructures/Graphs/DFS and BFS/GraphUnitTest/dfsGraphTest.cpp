#include "stdafx.h"
#include "CppUnitTest.h"
#include "dfs.h"
#include "Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dfs;

namespace GraphUnitTest
{
	TEST_CLASS(GraphPathClassTests)
	{
	public:

		TEST_METHOD(CheckConstruct)
		{
			Graph graph(13);
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

			Paths<Graph> paths(graph, 0);
		}		

		TEST_METHOD(CheckWrongConstruct)
		{
			Graph graph(3);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);

			try
			{
				Paths<Graph> paths(graph, -1);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckHasPathTo)
		{
			Graph graph(13);
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

			Paths<Graph> paths(graph, 0);
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
			Graph graph(13);
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

			Paths<Graph> paths(graph, 11);
			Assert::AreEqual(paths.hasPathTo(1), false);
			Assert::AreEqual(paths.hasPathTo(2), false);
			Assert::AreEqual(paths.hasPathTo(3), false);
			Assert::AreEqual(paths.hasPathTo(4), false);
			Assert::AreEqual(paths.hasPathTo(5), false);
			Assert::AreEqual(paths.hasPathTo(6), false);

			Assert::AreEqual(paths.hasPathTo(7), false);
			Assert::AreEqual(paths.hasPathTo(8), false);

			Assert::AreEqual(paths.hasPathTo(9), true);
			Assert::AreEqual(paths.hasPathTo(10), true);
			Assert::AreEqual(paths.hasPathTo(11), true);
			Assert::AreEqual(paths.hasPathTo(12), true);
		}

		bool equalStacks(Paths<Graph>::VertexStack lhs, Paths<Graph>::VertexStack rhs)
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
			Graph graph(13);
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

			Paths<Graph> paths(graph, 0);
			
			Paths<Graph>::VertexStack etalon6;
			etalon6.push(6);
			etalon6.push(0);
			Paths<Graph>::VertexStack expected6 = paths.pathTo(6);
			Assert::IsTrue(equalStacks(etalon6, expected6));

			Paths<Graph>::VertexStack etalon3;
			etalon3.push(3);
			etalon3.push(4);
			etalon3.push(6);
			etalon3.push(0);
			Paths<Graph>::VertexStack expected3 = paths.pathTo(3);
			Assert::IsTrue(equalStacks(etalon3, expected3));

			Paths<Graph>::VertexStack etalon5;
			etalon5.push(5);
			etalon5.push(3);
			etalon5.push(4);
			etalon5.push(6);
			etalon5.push(0);
			Paths<Graph>::VertexStack expected5 = paths.pathTo(5);
			Assert::IsTrue(equalStacks(etalon5, expected5));

			Paths<Graph>::VertexStack stack8 = paths.pathTo(8);
			Assert::IsTrue(stack8.empty());
			
			Paths<Graph>::VertexStack stack12 = paths.pathTo(12);
			Assert::IsTrue(stack12.empty());
		}

		TEST_METHOD(CheckPathTo2)
		{
			Graph graph(13);
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

			Paths<Graph> paths(graph, 12);

			Paths<Graph>::VertexStack etalon11;
			etalon11.push(11);
			etalon11.push(9);
			etalon11.push(12);
			Paths<Graph>::VertexStack expected11 = paths.pathTo(11);
			Assert::IsTrue(equalStacks(etalon11, expected11));

			Paths<Graph>::VertexStack etalon10;
			etalon10.push(10);
			etalon10.push(9);
			etalon10.push(12);
			Paths<Graph>::VertexStack expected10 = paths.pathTo(10);
			Assert::IsTrue(equalStacks(etalon10, expected10));

			Paths<Graph>::VertexStack stack8 = paths.pathTo(8);
			Assert::IsTrue(stack8.empty());

			Paths<Graph>::VertexStack stack2 = paths.pathTo(2);
			Assert::IsTrue(stack2.empty());
		}
	};
}