#include "stdafx.h"
#include "CppUnitTest.h"
#include "utils.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataCompressionTest
{
	TEST_CLASS(utilsUnitTest)
	{
	public:

		template <class T>
		void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
		{
			Assert::AreEqual(lhs.size(), rhs.size());
			Assert::IsTrue(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		TEST_METHOD(utilsUnitTest1)
		{
			std::vector<bool> expected = { 0, 1, 0, 0, 0, 0, 0, 1};
			std::vector<bool> actual = getBinaryRepresentation('A');
			checkTwoVectorsAreEqual(expected, actual);
		}
		
		TEST_METHOD(utilsUnitTest2)
		{
			std::vector<bool> expected = { 0, 1, 0, 0, 1, 0, 0, 1 };
			std::vector<bool> actual = getBinaryRepresentation('I');
			checkTwoVectorsAreEqual(expected, actual);
		}

		TEST_METHOD(utilsUnitTest3)
		{
			std::vector<bool> binaryRepresentation = { 0, 1, 0, 0, 0, 0, 0, 1 };
			Assert::AreEqual('A', getSymbol(binaryRepresentation));
		}

		TEST_METHOD(utilsUnitTest4)
		{
			std::vector<bool> binaryRepresentation = { 0, 1, 0, 0, 1, 0, 0, 1 };
			Assert::AreEqual('I', getSymbol(binaryRepresentation));
		}

		TEST_METHOD(utilsUnitTest5)
		{
			std::vector<bool> binaryRepresentation = { 0, 1, 0, 0, 1, 0, 0 };
			Assert::AreEqual('\0', getSymbol(binaryRepresentation));
		}

		TEST_METHOD(utilsUnitTest6)
		{
			std::vector<bool> binaryRepresentation = { 0, 1, 0, 0, 1, 0, 0, 0, 0};
			Assert::AreEqual('\0', getSymbol(binaryRepresentation));
		}
	};
}