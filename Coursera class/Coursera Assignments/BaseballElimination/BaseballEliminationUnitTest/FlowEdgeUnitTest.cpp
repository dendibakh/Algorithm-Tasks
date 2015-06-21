#include "stdafx.h"
#include "CppUnitTest.h"
#include "FlowEdge.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EWGraphUnitTest
{
	TEST_CLASS(EdgeUnitTest)
	{
	public:
		
		TEST_METHOD(Construct)
		{
			FlowEdge e1(1, 0, 45);
			int v = e1.from();
			int w = e1.to();
			Assert::AreEqual(v, 1);
			Assert::AreEqual(w, 0);
			Assert::AreEqual(e1.getCapacity(), 45);
			Assert::AreEqual(e1.getFlow(), 0);
		}

		TEST_METHOD(CopyConstruct)
		{
			FlowEdge e1(0, 2, 36);
			FlowEdge e2(e1);
			int v = e2.from();
			int w = e2.to();
			Assert::AreEqual(v, 0);
			Assert::AreEqual(w, 2);
			Assert::AreEqual(e2.getCapacity(), 36);
			Assert::AreEqual(e2.getFlow(), 0);
		}

		TEST_METHOD(AssignOperator)
		{
			FlowEdge e1(0, 2, 36);
			FlowEdge e2(10, 3, 22);
			int v = e2.from();
			int w = e2.to();
			Assert::AreEqual(v, 10);
			Assert::AreEqual(w, 3);
			Assert::AreEqual(e2.getCapacity(), 22);
			Assert::AreEqual(e2.getFlow(), 0);

			e2 = e1;

			int v_ = e2.from();
			int w_ = e2.to();
			Assert::AreEqual(v_, 0);
			Assert::AreEqual(w_, 2);
			Assert::AreEqual(e2.getCapacity(), 36);
			Assert::AreEqual(e2.getFlow(), 0);
		}

		TEST_METHOD(CheckGetResidualCapacityTo)
		{
			FlowEdge e1(1, 2, 36);
			Assert::AreEqual(e1.getResidualCapacityTo(1), 0);
			Assert::AreEqual(e1.getResidualCapacityTo(2), 36);
			try
			{
				Assert::AreEqual(e1.getResidualCapacityTo(0), 0);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception &)
			{
			}
		}

		TEST_METHOD(CheckAddResidualCapacityTo)
		{
			FlowEdge e1(1, 2, 36);

			e1.addResidualFlowTo(2, 10);
			Assert::AreEqual(e1.getResidualCapacityTo(1), 10);
			Assert::AreEqual(e1.getResidualCapacityTo(2), 26);
			Assert::AreEqual(e1.getCapacity(), 36);
			Assert::AreEqual(e1.getFlow(), 10);

			e1.addResidualFlowTo(1, 5);
			Assert::AreEqual(e1.getResidualCapacityTo(1), 5);
			Assert::AreEqual(e1.getResidualCapacityTo(2), 31);
			Assert::AreEqual(e1.getCapacity(), 36);
			Assert::AreEqual(e1.getFlow(), 5);
		}

		TEST_METHOD(CompareOperator)	
		{
			FlowEdge e1(0, 2, 36);
			FlowEdge e2(10, 3, 22);
			FlowEdge e3(0, 2, 36);
			FlowEdge e4(0, 2, 76);
			FlowEdge e5(1, 2, 36);
			FlowEdge e6(0, 3, 36);

			Assert::IsFalse(e1 == e2);
			Assert::IsTrue(e1 == e3);
			Assert::IsFalse(e1 == e4);
			Assert::IsFalse(e1 == e5);
			Assert::IsFalse(e1 == e6);
		}

		TEST_METHOD(OperatorLess)
		{
			FlowEdge e1(1, 2, 36);
			FlowEdge e2(1, 2, 36);
			FlowEdge e3(1, 2, 22);
			FlowEdge e4(1, 2, 76);
			FlowEdge e5(2, 2, 76);
			FlowEdge e6(1, 3, 76);
			FlowEdge e7(3, 3, 76);
			FlowEdge e8(0, 0, 76);
			FlowEdge e9(0, 0, 22);
			FlowEdge e10(3, 3, 22);

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
			FlowEdge e1(1, 2, 36);
			
			Assert::AreEqual(e1.toString(), std::string("1 - 2 0/36"));
		}
	};
}