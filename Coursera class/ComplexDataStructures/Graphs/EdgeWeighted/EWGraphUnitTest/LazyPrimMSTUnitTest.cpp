#include "stdafx.h"
#include "CppUnitTest.h"
#include "LazyPrimMST.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EWGraphUnitTest
{
	TEST_CLASS(LazyPrimMSTUnitTest)
	{
	public:
		
		TEST_METHOD(ConstructMST)
		{
			EWGraph graph(8);
			graph.addEdge(Edge(0, 7, 0.16));
			graph.addEdge(Edge(2, 3, 0.17));
			graph.addEdge(Edge(1, 7, 0.19));
			graph.addEdge(Edge(0, 2, 0.26));
			graph.addEdge(Edge(5, 7, 0.28));
			graph.addEdge(Edge(1, 3, 0.29));
			graph.addEdge(Edge(1, 5, 0.32));
			graph.addEdge(Edge(2, 7, 0.34));
			graph.addEdge(Edge(4, 5, 0.35));
			graph.addEdge(Edge(1, 2, 0.36));
			graph.addEdge(Edge(4, 7, 0.37));
			graph.addEdge(Edge(0, 4, 0.38));
			graph.addEdge(Edge(6, 2, 0.40));

			LazyPrimMST mst(graph);
		}

		TEST_METHOD(ComputeMST)
		{
			EWGraph graph(8);
			graph.addEdge(Edge(0, 7, 0.16));
			graph.addEdge(Edge(2, 3, 0.17));
			graph.addEdge(Edge(1, 7, 0.19));
			graph.addEdge(Edge(0, 2, 0.26));
			graph.addEdge(Edge(5, 7, 0.28));
			graph.addEdge(Edge(1, 3, 0.29));
			graph.addEdge(Edge(1, 5, 0.32));
			graph.addEdge(Edge(2, 7, 0.34));
			graph.addEdge(Edge(4, 5, 0.35));
			graph.addEdge(Edge(1, 2, 0.36));
			graph.addEdge(Edge(4, 7, 0.37));
			graph.addEdge(Edge(0, 4, 0.38));
			graph.addEdge(Edge(2, 6, 0.40));

			LazyPrimMST::MSTEdgesContainer container;
			container.push_back(Edge(0, 7, 0.16));
			container.push_back(Edge(7, 1, 0.19));
			container.push_back(Edge(0, 2, 0.26));
			container.push_back(Edge(2, 3, 0.17));
			container.push_back(Edge(7, 5, 0.28));
			container.push_back(Edge(5, 4, 0.35));
			container.push_back(Edge(2, 6, 0.40));

			LazyPrimMST mst(graph);
			LazyPrimMST::MSTEdgesContainer mstEdges = mst.edges();
			Assert::IsTrue(std::equal(container.begin(), container.end(), mstEdges.begin()));
			Assert::AreEqual(mst.getWeight(), 1.81);
		}
	};
}