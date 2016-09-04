#include "stdafx.h"
#include "CppUnitTest.h"
#include "StrongConnectedComponents.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace StrConComp;

namespace StrConCompTest
{
	TEST_CLASS(StrongConnectedComponentsTest)
	{
	public:

		TEST_METHOD(Construct)
		{
			DiGraph graph(0);
			StrongConnectedComponents scc(graph);
		}

		TEST_METHOD(CheckCount)
		{
			DiGraph graph(7);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 5);
			graph.addEdge(5, 2);
			graph.addEdge(6, 0);
			graph.addEdge(3, 2);
			graph.addEdge(3, 5);
			graph.addEdge(3, 6);
			graph.addEdge(3, 4);
			graph.addEdge(6, 4);
			graph.addEdge(1, 4);

			StrongConnectedComponents scc(graph);
			Assert::AreEqual(scc.getComponentsCount(), 7);
			Assert::IsFalse(scc.isAnyCycles());
			StrongConnectedComponents::ComponentsContainer compVect = scc.getComponents();
			Assert::AreEqual(compVect[0][0], 3);
			Assert::AreEqual(compVect[1][0], 6);
			Assert::AreEqual(compVect[2][0], 0);
			Assert::AreEqual(compVect[3][0], 1);
			Assert::AreEqual(compVect[4][0], 5);
			Assert::AreEqual(compVect[5][0], 2);
			Assert::AreEqual(compVect[6][0], 4);
		}

		TEST_METHOD(CheckCountWithCycle)
		{
			DiGraph graph(7);
			graph.addEdge(0, 1);
			graph.addEdge(0, 2);
			graph.addEdge(0, 5);
			graph.addEdge(5, 2);
			graph.addEdge(6, 0);
			graph.addEdge(2, 3);
			graph.addEdge(3, 5);
			graph.addEdge(3, 6);
			graph.addEdge(3, 4);
			graph.addEdge(6, 4);
			graph.addEdge(1, 4);

			StrongConnectedComponents scc(graph);
			Assert::AreEqual(scc.getComponentsCount(), 3);
			Assert::IsTrue(scc.isAnyCycles());
			StrongConnectedComponents::ComponentsContainer compVect = scc.getComponents();
			Assert::AreEqual(compVect[0][0], 0);
			Assert::AreEqual(compVect[0][1], 2);
			Assert::AreEqual(compVect[0][2], 3);
			Assert::AreEqual(compVect[0][3], 5);
			Assert::AreEqual(compVect[0][4], 6);
			Assert::AreEqual(compVect[1][0], 1);
			Assert::AreEqual(compVect[2][0], 4);
		}
	};
}