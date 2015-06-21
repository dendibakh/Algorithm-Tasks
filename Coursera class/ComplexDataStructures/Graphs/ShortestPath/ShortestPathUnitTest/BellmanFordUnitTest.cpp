#include "stdafx.h"
#include "CppUnitTest.h"
#include "Bellman-FordSP.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShortestPathUnitTest
{
	TEST_CLASS(BellmanFordUnitTest)
	{
	public:
		
		bool equalStacks(BellmanFordSP::PathToStack lhs, BellmanFordSP::PathToStack rhs)
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

		TEST_METHOD(CheckShortestPath)
		{
			EWDiGraph graph(8);
			graph.addEdge(Edge(0, 1, 5.0));
			graph.addEdge(Edge(0, 4, 9.0));
			graph.addEdge(Edge(0, 7, 8.0));
			graph.addEdge(Edge(1, 2, 12.0));
			graph.addEdge(Edge(1, 3, 15.0));
			graph.addEdge(Edge(1, 7, 4.0));
			graph.addEdge(Edge(2, 3, 3.0));
			graph.addEdge(Edge(2, 6, 11.0));
			graph.addEdge(Edge(3, 6, 9.0));
			graph.addEdge(Edge(4, 5, 4.0));
			graph.addEdge(Edge(4, 6, 20.0));
			graph.addEdge(Edge(4, 7, 5.0));
			graph.addEdge(Edge(5, 2, 1.0));
			graph.addEdge(Edge(5, 6, 13.0));
			graph.addEdge(Edge(7, 5, 6.0));
			graph.addEdge(Edge(7, 2, 7.0));

			BellmanFordSP DSP(graph, 0);
			Assert::AreEqual(0.0, DSP.distTo(0));
			Assert::AreEqual(5.0, DSP.distTo(1));
			Assert::AreEqual(14.0, DSP.distTo(2));
			Assert::AreEqual(17.0, DSP.distTo(3));
			Assert::AreEqual(9.0, DSP.distTo(4));
			Assert::AreEqual(13.0, DSP.distTo(5));
			Assert::AreEqual(25.0, DSP.distTo(6));
			Assert::AreEqual(8.0, DSP.distTo(7));

			Assert::IsTrue(DSP.hasPathTo(0));
			Assert::IsTrue(DSP.hasPathTo(1));
			Assert::IsTrue(DSP.hasPathTo(2));
			Assert::IsTrue(DSP.hasPathTo(3));
			Assert::IsTrue(DSP.hasPathTo(4));
			Assert::IsTrue(DSP.hasPathTo(5));
			Assert::IsTrue(DSP.hasPathTo(6));
			Assert::IsTrue(DSP.hasPathTo(7));

			BellmanFordSP::PathToStack etalon;
			etalon.push(3);
			etalon.push(2);
			etalon.push(5);
			etalon.push(4);
			etalon.push(0);
			BellmanFordSP::PathToStack actual = DSP.pathTo(3);
			Assert::IsTrue(equalStacks(etalon, actual));

			BellmanFordSP::PathToStack etalon2;
			etalon2.push(6);
			etalon2.push(2);
			etalon2.push(5);
			etalon2.push(4);
			etalon2.push(0);
			BellmanFordSP::PathToStack actual2 = DSP.pathTo(6);
			Assert::IsTrue(equalStacks(etalon2, actual2));

			BellmanFordSP::PathToStack etalon3;
			etalon3.push(7);
			etalon3.push(0);
			BellmanFordSP::PathToStack actual3 = DSP.pathTo(7);
			Assert::IsTrue(equalStacks(etalon3, actual3));

			BellmanFordSP::PathToStack etalon4;
			etalon4.push(1);
			etalon4.push(0);
			BellmanFordSP::PathToStack actual4 = DSP.pathTo(1);
			Assert::IsTrue(equalStacks(etalon4, actual4));
			Assert::IsFalse(DSP.hasNegativeCycle());
		}

		TEST_METHOD(CheckNegativeCycles)
		{
			EWDiGraph graph(8);
			graph.addEdge(Edge(5, 4, -0.66));
			graph.addEdge(Edge(4, 7, 0.37));
			graph.addEdge(Edge(5, 7, 0.28));
			graph.addEdge(Edge(7, 5, 0.28));
			graph.addEdge(Edge(5, 1, 0.32));
			graph.addEdge(Edge(0, 4, 0.38));
			graph.addEdge(Edge(0, 2, 0.26));
			graph.addEdge(Edge(7, 3, 0.39));
			graph.addEdge(Edge(1, 3, 0.29));
			graph.addEdge(Edge(2, 7, 0.34));
			graph.addEdge(Edge(6, 2, 0.40));
			graph.addEdge(Edge(3, 6, 0.52));
			graph.addEdge(Edge(6, 0, 0.58));
			graph.addEdge(Edge(6, 4, 0.93));

			BellmanFordSP DSP(graph, 0);
			Assert::IsTrue(DSP.hasNegativeCycle());

			BellmanFordSP::PathToStack etalon;
			etalon.push(5);
			etalon.push(7);
			etalon.push(4);
			BellmanFordSP::PathToStack actual = DSP.getNegativeCycle();
			Assert::IsTrue(equalStacks(etalon, actual));
		}

		TEST_METHOD(CheckNegativeCycles2)
		{
			EWDiGraph graph(8);
			graph.addEdge(Edge(5, 4, -0.64));
			graph.addEdge(Edge(4, 7, 0.37));
			graph.addEdge(Edge(5, 7, 0.28));
			graph.addEdge(Edge(7, 5, 0.28));
			graph.addEdge(Edge(5, 1, 0.32));
			graph.addEdge(Edge(0, 4, 0.38));
			graph.addEdge(Edge(0, 2, 0.26));
			graph.addEdge(Edge(7, 3, 0.39));
			graph.addEdge(Edge(1, 3, 0.29));
			graph.addEdge(Edge(2, 7, 0.34));
			graph.addEdge(Edge(6, 2, 0.40));
			graph.addEdge(Edge(3, 6, 0.52));
			graph.addEdge(Edge(6, 0, 0.58));
			graph.addEdge(Edge(6, 4, 0.93));

			BellmanFordSP DSP(graph, 0);
			Assert::IsFalse(DSP.hasNegativeCycle());
		}
	};
}