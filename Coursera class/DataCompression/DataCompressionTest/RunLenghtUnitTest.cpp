#include "stdafx.h"
#include "CppUnitTest.h"
#include "RunLenghtCoding.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RunLeghtCoding;

namespace DataCompressionTest
{		
	TEST_CLASS(RunLenghtCodingUnitTest)
	{
	public:
		
		template <class T>
		void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
		{
			Assert::AreEqual(lhs.size(), rhs.size());
			Assert::IsTrue(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		TEST_METHOD(RunLenghtCodingUnitTest1)
		{
			std::vector<bool> text = { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0 };
			compressedResult expected = { 0, 1, 5, 4, 1, 1, 2, 1, 1, 1, 1, 1 };
			compressedResult actual = compress(text);
			checkTwoVectorsAreEqual(expected, actual);
		}

		TEST_METHOD(RunLenghtCodingUnitTest2)
		{
			std::vector<bool> text = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
				                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 };
			compressedResult expected = { 0, 12, 9, 1, 11, 13, 1, 1, 1, 1, 1, 1, 8, 3, 5 };
			compressedResult actual = compress(text);
			checkTwoVectorsAreEqual(expected, actual);
		}

		TEST_METHOD(RunLenghtCodingUnitTest3)
		{
			std::vector<bool> text = { 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 };
			compressedResult expected = { 1, 4, 5, 3, 2 };
			compressedResult actual = compress(text);
			checkTwoVectorsAreEqual(expected, actual);
		}

		TEST_METHOD(RunLenghtCodingUnitTest4)
		{
			compressedResult compressedText = { 0, 1, 5, 4, 1, 1, 2, 1, 1, 1, 1, 1 };
			std::vector<bool> expected = { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0 };
			std::vector<bool> actual = expand(compressedText);
			checkTwoVectorsAreEqual(expected, actual);
		}

		TEST_METHOD(RunLenghtCodingUnitTest5)
		{
			compressedResult compressedText = { 0, 12, 9, 1, 11, 13, 1, 1, 1, 1, 1, 1, 8, 3, 5 };
			std::vector<bool> expected = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
							               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 };
			std::vector<bool> actual = expand(compressedText);
			checkTwoVectorsAreEqual(expected, actual);
		}

		TEST_METHOD(RunLenghtCodingUnitTest6)
		{
			compressedResult compressedText = { 1, 4, 5, 3, 2 };
			std::vector<bool> expected = { 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 };
			std::vector<bool> actual = expand(compressedText);
			checkTwoVectorsAreEqual(expected, actual);
		}
		
		TEST_METHOD(RunLenghtCodingUnitTest7)
		{
			std::vector<bool> text = {};
			compressedResult expected = {};
			compressedResult actual = compress(text);
			checkTwoVectorsAreEqual(expected, actual);
		}

		TEST_METHOD(RunLenghtCodingUnitTest8)
		{
			compressedResult text = {};
			std::vector<bool> expected = {};
			std::vector<bool> actual = expand(text);
			checkTwoVectorsAreEqual(expected, actual);
		}

		TEST_METHOD(RunLenghtCodingUnitTest9)
		{
			std::string text = "AXDFCD";
			compressedResult expected = { 0, 1, 1, 5, 1, 1, 1, 1, 2, 4, 1, 3, 1, 3, 1, 3, 2, 2, 1, 4, 2, 1, 1, 3, 1, 2 };
			compressedResult actual = compress(text);
			checkTwoVectorsAreEqual(expected, actual);
		}
	};
}