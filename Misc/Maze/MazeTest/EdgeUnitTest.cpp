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
                        Edge e1(1, 0);
                        int v = e1.from();
                        int w = e1.to();
                        Assert::AreEqual(v, 1);
                        Assert::AreEqual(w, 0);
                }

                TEST_METHOD(CopyConstruct)
                {
                        Edge e1(0, 2);
                        Edge e2(e1);
                        int v = e2.from();
                        int w = e2.to();
                        Assert::AreEqual(v, 0);
                        Assert::AreEqual(w, 2);
                }

                TEST_METHOD(AssignOperator)
                {
                        Edge e1(0, 2);
                        Edge e2(10, 3);
                        int v = e2.from();
                        int w = e2.to();
                        Assert::AreEqual(v, 10);
                        Assert::AreEqual(w, 3);

                        e2 = e1;

                        int v_ = e2.from();
                        int w_ = e2.to();
                        Assert::AreEqual(v_, 0);
                        Assert::AreEqual(w_, 2);
                }

                TEST_METHOD(CompareOperator)
                {
                        Edge e1(0, 2);
                        Edge e2(10, 3);
                        Edge e3(0, 2);
                        Edge e4(1, 2);
                        Edge e5(0, 3);

                        Assert::IsFalse(e1 == e2);
                        Assert::IsTrue(e1 == e3);
                        Assert::IsFalse(e1 == e4);
                        Assert::IsFalse(e1 == e5);

                        Assert::IsTrue(e3 == e1);
                        Assert::IsFalse(e3 == e2);
                        Assert::IsFalse(e3 == e5);
                }

                TEST_METHOD(CheckToString)
                {
                        Edge e1(1, 2);
                        
                        Assert::AreEqual(e1.toString(), std::string("1 - 2"));
                }
        };
}