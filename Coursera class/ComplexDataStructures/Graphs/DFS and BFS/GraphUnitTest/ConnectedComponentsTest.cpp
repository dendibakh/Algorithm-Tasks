#include "stdafx.h"
#include "CppUnitTest.h"
#include "ConectedComponents.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace cc;

namespace GraphUnitTest
{
	TEST_CLASS(ConnectedComponentsTest)
	{
	public:
		
		TEST_METHOD(Construct)
		{
			Graph graph(0);
			ConnectedComponents cc_(graph);
		}

		TEST_METHOD(CheckConnected)
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

			ConnectedComponents cc_(graph);
			Assert::IsTrue(cc_.connected(0, 1));
			Assert::IsTrue(cc_.connected(0, 2));
			Assert::IsTrue(cc_.connected(0, 3));
			Assert::IsTrue(cc_.connected(0, 4));
			Assert::IsTrue(cc_.connected(0, 5));
			Assert::IsTrue(cc_.connected(0, 6));
			Assert::IsTrue(cc_.connected(0, 0));
			Assert::IsTrue(cc_.connected(1, 1));
			Assert::IsTrue(cc_.connected(1, 2));
			Assert::IsTrue(cc_.connected(1, 6));
			Assert::IsTrue(cc_.connected(1, 5));
			Assert::IsTrue(cc_.connected(1, 3));
			Assert::IsTrue(cc_.connected(1, 4));
			Assert::IsTrue(cc_.connected(1, 4));
			Assert::IsTrue(cc_.connected(3, 5));
			Assert::IsTrue(cc_.connected(6, 4));
			Assert::IsTrue(cc_.connected(6, 5));

			Assert::IsFalse(cc_.connected(0, 7));
			Assert::IsFalse(cc_.connected(1, 8));
			Assert::IsFalse(cc_.connected(2, 9));
			Assert::IsFalse(cc_.connected(3, 10));
			Assert::IsFalse(cc_.connected(4, 11));
			Assert::IsFalse(cc_.connected(5, 12));
			Assert::IsFalse(cc_.connected(6, 8));
		}

		TEST_METHOD(CheckId)
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

			ConnectedComponents cc_(graph);
			Assert::AreEqual(cc_.id(0), 0);
			Assert::AreEqual(cc_.id(1), 0);
			Assert::AreEqual(cc_.id(2), 0);
			Assert::AreEqual(cc_.id(3), 0);
			Assert::AreEqual(cc_.id(4), 0);
			Assert::AreEqual(cc_.id(5), 0);
			Assert::AreEqual(cc_.id(6), 0);

			Assert::AreEqual(cc_.id(7), 1);
			Assert::AreEqual(cc_.id(8), 1);

			Assert::AreEqual(cc_.id(9), 2);
			Assert::AreEqual(cc_.id(10), 2);
			Assert::AreEqual(cc_.id(11), 2);
			Assert::AreEqual(cc_.id(12), 2);
		}

		TEST_METHOD(CheckCount)
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

			ConnectedComponents cc_(graph);
			Assert::AreEqual(cc_.count(), 3);
		}
	};
}