#include "stdafx.h"
#include "CppUnitTest.h"
#include "LongestPath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShortestPathUnitTest
{
	TEST_CLASS(LongestPathUnitTest)
	{
	public:
		
		bool equalStacks(LongestPath::PathToStack lhs, LongestPath::PathToStack rhs)
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

		TEST_METHOD(CheckLongestPath)
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

			LongestPath DSP(graph, 0);

			Assert::IsTrue(DSP.hasPathTo(0));
			Assert::IsTrue(DSP.hasPathTo(1));
			Assert::IsTrue(DSP.hasPathTo(2));
			Assert::IsTrue(DSP.hasPathTo(3));
			Assert::IsTrue(DSP.hasPathTo(4));
			Assert::IsTrue(DSP.hasPathTo(5));
			Assert::IsTrue(DSP.hasPathTo(6));
			Assert::IsTrue(DSP.hasPathTo(7));

			Assert::AreEqual(0.0, DSP.distTo(0));
			Assert::AreEqual(5.0, DSP.distTo(1));

			LongestPath::PathToStack etalon4;
			etalon4.push(1);
			etalon4.push(0);
			LongestPath::PathToStack actual4 = DSP.pathTo(1);
			Assert::IsTrue(equalStacks(etalon4, actual4));
			
			Assert::AreEqual(24.0, DSP.distTo(3));

			LongestPath::PathToStack etalon;
			etalon.push(3);
			etalon.push(2);
			etalon.push(7);
			etalon.push(4);
			etalon.push(0);
			LongestPath::PathToStack actual = DSP.pathTo(3);
			Assert::IsTrue(equalStacks(etalon, actual));

			Assert::AreEqual(33.0, DSP.distTo(6));

			LongestPath::PathToStack etalon2;
			etalon2.push(6);
			etalon2.push(3);
			etalon2.push(2);
			etalon2.push(7);
			etalon2.push(4);
			etalon2.push(0);
			LongestPath::PathToStack actual2 = DSP.pathTo(6);
			Assert::IsTrue(equalStacks(etalon2, actual2));

			Assert::AreEqual(14.0, DSP.distTo(7));
			
			LongestPath::PathToStack etalon3;
			etalon3.push(7);
			etalon3.push(4);
			etalon3.push(0);
			LongestPath::PathToStack actual3 = DSP.pathTo(7);
			Assert::IsTrue(equalStacks(etalon3, actual3));

			Assert::AreEqual(21.0, DSP.distTo(2));
			Assert::AreEqual(9.0, DSP.distTo(4));
			Assert::AreEqual(20.0, DSP.distTo(5));
		}

	};
}