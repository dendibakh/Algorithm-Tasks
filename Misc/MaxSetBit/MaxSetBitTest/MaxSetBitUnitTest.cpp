#include "stdafx.h"
#include "maxSetBit.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace MaxSetBitTest
{
	[TestClass]
	public ref class MaxSetBitUnitTest
	{
	public: 
		[TestMethod]
		void TestBinaryRepresentation1()
		{
			bool etalon_arr[] = { 0, 1, 0, 1, 0, 0, 0, 0 };
			std::vector<bool> etalon(etalon_arr, etalon_arr + sizeof(etalon_arr) / sizeof(etalon_arr[0]));
			unsigned char c = 10;
			std::vector<bool> result = binaryRepresentation(c);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), result.begin()));
		}
		
		[TestMethod]
		void TestBinaryRepresentation2()
		{
			bool etalon_arr[] = { 1, 1, 1, 0, 0, 1, 1, 0 };
			std::vector<bool> etalon(etalon_arr, etalon_arr + sizeof(etalon_arr) / sizeof(etalon_arr[0]));
			unsigned char c = 103;
			std::vector<bool> result = binaryRepresentation(c);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), result.begin()));
		}

		[TestMethod]
		void TestBinaryRepresentation3()
		{
			bool etalon_arr[] = { 1, 1, 0, 1, 1, 0, 0, 1 };
			std::vector<bool> etalon(etalon_arr, etalon_arr + sizeof(etalon_arr) / sizeof(etalon_arr[0]));
			unsigned char c = 155;
			std::vector<bool> result = binaryRepresentation(c);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), result.begin()));
		}

		[TestMethod]
		void TestBinaryRepresentation4()
		{
			bool etalon_arr[] = { 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0 };
			std::vector<bool> etalon(etalon_arr, etalon_arr + sizeof(etalon_arr) / sizeof(etalon_arr[0]));
			unsigned short c = 15507;
			std::vector<bool> result = binaryRepresentation(c);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), result.begin()));
		}

		[TestMethod]
		void TestBinaryRepresentation5()
		{
			bool etalon_arr[] = { 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			std::vector<bool> etalon(etalon_arr, etalon_arr + sizeof(etalon_arr) / sizeof(etalon_arr[0]));
			unsigned int c = 1550754;
			std::vector<bool> result = binaryRepresentation(c);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), result.begin()));
		}

		[TestMethod]
		void TestCastToBinary()
		{
			unsigned char c1 = 10;
			unsigned char c2 = 103;
			unsigned char c3 = 155;
			unsigned short c4 = 15507;
			unsigned int c5 = 1550754;
			using namespace CastToBinary;
			Assert::AreEqual(3U, findLeftMostSetBit(c1));
			Assert::AreEqual(6U, findLeftMostSetBit(c2));
			Assert::AreEqual(7U, findLeftMostSetBit(c3));
			Assert::AreEqual(13U, findLeftMostSetBit(c4));
			Assert::AreEqual(20U, findLeftMostSetBit(c5));
			// duration - 00:00:00.0048792
		}

		[TestMethod]
		void TestPutMask()
		{
			unsigned char c1 = 10;
			unsigned char c2 = 103;
			unsigned char c3 = 155;
			unsigned short c4 = 15507;
			unsigned int c5 = 1550754;
			using namespace PutMask;
			Assert::AreEqual(3U, findLeftMostSetBit(c1));
			Assert::AreEqual(6U, findLeftMostSetBit(c2));
			Assert::AreEqual(7U, findLeftMostSetBit(c3));
			Assert::AreEqual(13U, findLeftMostSetBit(c4));
			Assert::AreEqual(20U, findLeftMostSetBit(c5));
			// duration - 00:00:00.0006888
		}

		[TestMethod]
		void TestBinarySearchMask()
		{
			unsigned char c1 = 10;
			unsigned char c2 = 103;
			unsigned char c3 = 155;
			unsigned short c4 = 15507;
			unsigned int c5 = 1550754;
			using namespace BinarySearchMask;
			Assert::AreEqual(3U, findLeftMostSetBit(c1));
			Assert::AreEqual(6U, findLeftMostSetBit(c2));
			Assert::AreEqual(7U, findLeftMostSetBit(c3));
			Assert::AreEqual(13U, findLeftMostSetBit(c4));
			Assert::AreEqual(20U, findLeftMostSetBit(c5));
			// duration - 00:00:00.0009363
		}
	};
}
