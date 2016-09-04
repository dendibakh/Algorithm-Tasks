#include "stdafx.h"
#include "CppUnitTest.h"
#include "UnionFind.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EWGraphUnitTest
{
	TEST_CLASS(UnionFindUnitTest)
	{
	public:
		
		TEST_METHOD(CheckConstruct)
		{
			UnionFind uf(10);
			Assert::AreEqual(10, uf.getCount());
			Assert::IsFalse(uf.connected(0, 1));
			Assert::IsFalse(uf.connected(0, 9));
			Assert::IsFalse(uf.connected(0, 8));
			Assert::IsFalse(uf.connected(0, 5));
			Assert::IsFalse(uf.connected(5, 8));
			Assert::IsFalse(uf.connected(3, 7));
			Assert::IsFalse(uf.connected(9, 2));

			Assert::AreEqual(0, uf.find(0));
			Assert::AreEqual(1, uf.find(1));
			Assert::AreEqual(3, uf.find(3));
			Assert::AreEqual(5, uf.find(5));
			Assert::AreEqual(7, uf.find(7));
			Assert::AreEqual(8, uf.find(8));
			Assert::AreEqual(9, uf.find(9));
		}

		TEST_METHOD(CheckWrongIndex)
		{
			UnionFind uf(10);
			try
			{
				Assert::IsFalse(uf.connected(0, 10));
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckConnectedAndUnion)
		{
			UnionFind uf(10);
			uf.unionElems(0, 9);
			uf.unionElems(5, 2);
			uf.unionElems(3, 7);
			uf.unionElems(5, 9);
			uf.unionElems(6, 8);
			uf.unionElems(4, 8);

			Assert::IsTrue(uf.connected(9, 2));
			Assert::IsTrue(uf.connected(5, 2));
			Assert::IsTrue(uf.connected(0, 2));
			Assert::IsTrue(uf.connected(9, 5));
			
			Assert::IsTrue(uf.connected(3, 7));

			Assert::IsTrue(uf.connected(6, 4));
			Assert::IsTrue(uf.connected(6, 8));
			Assert::IsTrue(uf.connected(8, 4));

			Assert::IsFalse(uf.connected(9, 4));
			Assert::IsFalse(uf.connected(9, 6));
			Assert::IsFalse(uf.connected(9, 8));
			Assert::IsFalse(uf.connected(9, 7));
			Assert::IsFalse(uf.connected(9, 3));

			Assert::IsFalse(uf.connected(3, 2));
			Assert::IsFalse(uf.connected(3, 5));
			Assert::IsFalse(uf.connected(3, 0));

			Assert::IsFalse(uf.connected(2, 7));
			Assert::IsFalse(uf.connected(2, 8));
			Assert::IsFalse(uf.connected(2, 6));
			Assert::IsFalse(uf.connected(2, 4));
			Assert::IsFalse(uf.connected(5, 7));
			Assert::IsFalse(uf.connected(5, 8));
			Assert::IsFalse(uf.connected(5, 6));
			Assert::IsFalse(uf.connected(5, 4));
		}
	};
}