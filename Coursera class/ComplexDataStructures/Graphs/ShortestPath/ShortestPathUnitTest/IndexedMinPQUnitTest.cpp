#include "stdafx.h"
#include "CppUnitTest.h"
#include "IndexedMinPQ.h"
#include <string>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EWGraphUnitTest
{
	TEST_CLASS(IndexedMinPQUnitTest)
	{
	public:
		
		TEST_METHOD(CheckDelMin)
		{
			IndexedMinPQ<int> pq(10);
			pq.insert(0, 5);
			pq.insert(1, 3);
			pq.insert(2, 7);
			pq.insert(3, 4);
			pq.insert(4, 8);
			pq.insert(5, 2);
			pq.insert(6, 9);
			pq.insert(7, 0);
			pq.insert(8, 1);
			pq.insert(9, 6);
			
			Assert::AreEqual(0, pq.minKey());
			Assert::AreEqual(7, pq.delMin());
			Assert::AreEqual(1, pq.minKey());
			Assert::AreEqual(8, pq.delMin());
			Assert::AreEqual(2, pq.minKey());
			Assert::AreEqual(5, pq.delMin());
			Assert::AreEqual(3, pq.minKey());
			Assert::AreEqual(1, pq.delMin());
			Assert::AreEqual(4, pq.minKey());
			Assert::AreEqual(3, pq.delMin());
			Assert::AreEqual(5, pq.minKey());
			Assert::AreEqual(0, pq.delMin());
			Assert::AreEqual(6, pq.minKey());
			Assert::AreEqual(9, pq.delMin());
			Assert::AreEqual(7, pq.minKey());
			Assert::AreEqual(2, pq.delMin());
			Assert::AreEqual(8, pq.minKey());
			Assert::AreEqual(4, pq.delMin());
			Assert::AreEqual(9, pq.minKey());
			Assert::AreEqual(6, pq.delMin());
		}

		TEST_METHOD(CheckDelMinWithInsetrs)
		{
			IndexedMinPQ<int> pq(8);
			pq.insert(0, 5);
			pq.insert(1, 3);
			pq.insert(2, 7);
			pq.insert(3, 4);
			pq.insert(4, 8);

			Assert::AreEqual(3, pq.minKey());
			Assert::AreEqual(1, pq.delMin());
			Assert::AreEqual(4, pq.minKey());
			Assert::AreEqual(3, pq.delMin());

			pq.insert(5, 1);
			pq.insert(6, 0);

			Assert::AreEqual(0, pq.minKey());
			Assert::AreEqual(6, pq.delMin());
			Assert::AreEqual(1, pq.minKey());
			Assert::AreEqual(5, pq.delMin());
		}

		TEST_METHOD(CheckDecreaseKey)
		{
			IndexedMinPQ<int> pq(8);
			pq.insert(pq.size(), 5);
			pq.insert(pq.size(), 3);
			pq.insert(pq.size(), 7);
			pq.insert(pq.size(), 4);
			pq.insert(pq.size(), 8);

			pq.decreaseKey(2, 2);
			Assert::AreEqual(2, pq.minKey());
			Assert::AreEqual(2, pq.delMin());
			pq.decreaseKey(1, 1);
			pq.decreaseKey(3, 0);
			Assert::AreEqual(0, pq.minKey());
			Assert::AreEqual(3, pq.delMin());
			Assert::AreEqual(1, pq.minKey());
			Assert::AreEqual(1, pq.delMin());
		}
	};
}