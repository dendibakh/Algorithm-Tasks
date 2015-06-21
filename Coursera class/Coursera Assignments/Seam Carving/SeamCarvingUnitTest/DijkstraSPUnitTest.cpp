#include "stdafx.h"
#include "DijkstraSP.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ShortestPathUnitTest
{
	[TestClass]
	public ref class DijkstraSPUnitTest
	{
	public:
		[TestMethod]
		void CheckShortestPath()
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

			DijkstraSP DSP(graph, 0);
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

			DijkstraSP::PathToStack etalon;
			etalon.push_back(3);
			etalon.push_back(2);
			etalon.push_back(5);
			etalon.push_back(4);
			etalon.push_back(0);
			DijkstraSP::PathToStack actual = DSP.pathTo(3);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));

			DijkstraSP::PathToStack etalon2;
			etalon2.push_back(6);
			etalon2.push_back(2);
			etalon2.push_back(5);
			etalon2.push_back(4);
			etalon2.push_back(0);
			DijkstraSP::PathToStack actual2 = DSP.pathTo(6);
			Assert::IsTrue(std::equal(etalon2.begin(), etalon2.end(), actual2.begin()));

			DijkstraSP::PathToStack etalon3;
			etalon3.push_back(7);
			etalon3.push_back(0);
			DijkstraSP::PathToStack actual3 = DSP.pathTo(7);
			Assert::IsTrue(std::equal(etalon3.begin(), etalon3.end(), actual3.begin()));

			DijkstraSP::PathToStack etalon4;
			etalon4.push_back(1);
			etalon4.push_back(0);
			DijkstraSP::PathToStack actual4 = DSP.pathTo(1);
			Assert::IsTrue(std::equal(etalon4.begin(), etalon4.end(), actual4.begin()));
		}

	};
}