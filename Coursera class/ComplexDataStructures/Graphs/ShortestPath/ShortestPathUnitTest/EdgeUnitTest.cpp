#include "stdafx.h"
#include "CppUnitTest.h"
#include "Edge.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EWGraphUnitTest
{
	TEST_CLASS(EdgeUnitTest)
	{
	public:
		
		TEST_METHOD(Construct)
		{
			Edge e1(1, 0, 0.45);
			int v = e1.from();
			int w = e1.to();
			Assert::AreEqual(v, 1);
			Assert::AreEqual(w, 0);
			Assert::AreEqual(e1.getWeight(), 0.45);
		}

		TEST_METHOD(CopyConstruct)
		{
			Edge e1(0, 2, 0.36);
			Edge e2(e1);
			int v = e2.from();
			int w = e2.to();
			Assert::AreEqual(v, 0);
			Assert::AreEqual(w, 2);
			Assert::AreEqual(e2.getWeight(), 0.36);
		}

		TEST_METHOD(AssignOperator)
		{
			Edge e1(0, 2, 0.36);
			Edge e2(10, 3, 0.22);
			int v = e2.from();
			int w = e2.to();
			Assert::AreEqual(v, 10);
			Assert::AreEqual(w, 3);
			Assert::AreEqual(e2.getWeight(), 0.22);

			e2 = e1;

			int v_ = e2.from();
			int w_ = e2.to();
			Assert::AreEqual(v_, 0);
			Assert::AreEqual(w_, 2);
			Assert::AreEqual(e2.getWeight(), 0.36);
		}

		TEST_METHOD(CompareOperator)
		{
			Edge e1(0, 2, 0.36);
			Edge e2(10, 3, 0.22);
			Edge e3(0, 2, 0.36);
			Edge e4(0, 2, 0.76);
			Edge e5(1, 2, 0.36);
			Edge e6(0, 3, 0.36);

			Assert::IsFalse(e1 == e2);
			Assert::IsTrue(e1 == e3);
			Assert::IsFalse(e1 == e4);
			Assert::IsFalse(e1 == e5);
			Assert::IsFalse(e1 == e6);
		}

		TEST_METHOD(OperatorLess)
		{
			Edge e1(1, 2, 0.36);
			Edge e2(1, 2, 0.36);
			Edge e3(1, 2, 0.22);
			Edge e4(1, 2, 0.76);
			Edge e5(2, 2, 0.76);
			Edge e6(1, 3, 0.76);
			Edge e7(3, 3, 0.76);
			Edge e8(0, 0, 0.76);
			Edge e9(0, 0, 0.22);
			Edge e10(3, 3, 0.22);

			Assert::IsFalse(e1 < e2);
			Assert::IsFalse(e1 < e3);
			Assert::IsTrue(e1 < e4);
			Assert::IsTrue(e1 < e5);
			Assert::IsTrue(e1 < e6);
			Assert::IsTrue(e1 < e7);
			Assert::IsTrue(e1 < e8);
			Assert::IsFalse(e1 < e9);
			Assert::IsFalse(e1 < e10);
		}

		TEST_METHOD(CheckToString)
		{
			Edge e1(1, 2, 0.36);
			
			Assert::AreEqual(e1.toString(), std::string("1 - 2 0.36"));
		}
	};
}