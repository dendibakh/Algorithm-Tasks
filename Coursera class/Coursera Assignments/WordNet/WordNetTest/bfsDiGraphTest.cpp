#include "stdafx.h"
#include "bfs.h"
#include "DiGraph.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace bfs;

namespace GraphUnitTest
{
	[TestClass]
	public ref class bfsDiGraphTest
	{
	public:

		[TestMethod]
		void CheckConstruct()
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

		[TestMethod]
		void CheckWrongConstruct()
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

		[TestMethod]
		void CheckHasPathTo()
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

		[TestMethod]
		void CheckHasPathTo2()
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

		[TestMethod]
		void CheckPathTo()
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

		[TestMethod]
		void CheckPathTo2()
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

			Paths<DiGraph>::VertexStack etalon12;
			etalon12.push(12);
			etalon12.push(9);
			Paths<DiGraph>::VertexStack expected12 = paths.pathTo(12);
			Assert::IsTrue(equalStacks(etalon12, expected12));

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

		[TestMethod]
		void CheckPathTo3()
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

			Paths<DiGraph> paths(graph, 12);

			Paths<DiGraph>::VertexStack stack9 = paths.pathTo(9);
			Assert::IsTrue(stack9.empty());

			Paths<DiGraph>::VertexStack stack11 = paths.pathTo(11);
			Assert::IsTrue(stack11.empty());

			Paths<DiGraph>::VertexStack stack10 = paths.pathTo(10);
			Assert::IsTrue(stack10.empty());

			Paths<DiGraph>::VertexStack stack8 = paths.pathTo(8);
			Assert::IsTrue(stack8.empty());

			Paths<DiGraph>::VertexStack stack2 = paths.pathTo(2);
			Assert::IsTrue(stack2.empty());
		}

		[TestMethod]
		void CheckDistanceTo()
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

			try
			{
				Assert::AreEqual(paths.distanceTo(12), -1);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}

			try
			{
				Assert::AreEqual(paths.distanceTo(8), -1);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}

			Assert::AreEqual(paths.distanceTo(0), 0);
			Assert::AreEqual(paths.distanceTo(1), 1);
			Assert::AreEqual(paths.distanceTo(2), 1);
			Assert::AreEqual(paths.distanceTo(3), 2);
			Assert::AreEqual(paths.distanceTo(4), 2);
			Assert::AreEqual(paths.distanceTo(5), 1);
			Assert::AreEqual(paths.distanceTo(6), 1);
		}

		[TestMethod]
		void CheckDistanceTo2()
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

			try
			{
				Assert::AreEqual(paths.distanceTo(6), -1);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}

			try
			{
				Assert::AreEqual(paths.distanceTo(8), -1);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}

			Assert::AreEqual(paths.distanceTo(9), 0);
			Assert::AreEqual(paths.distanceTo(10), 1);
			Assert::AreEqual(paths.distanceTo(11), 1);
			Assert::AreEqual(paths.distanceTo(12), 1);
		}
	};
}