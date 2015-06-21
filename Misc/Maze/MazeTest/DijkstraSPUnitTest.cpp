#include "stdafx.h"
#include "CppUnitTest.h"
#include "DijkstraSP.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShortestPathUnitTest
{
        TEST_CLASS(DijkstraSPUnitTest)
        {
        public:
                
                bool equalStacks(DijkstraSP::PathToStack lhs, DijkstraSP::PathToStack rhs)
                {
                        if (lhs.size() != rhs.size())
                                return false;
                        while (!lhs.empty())
                        {
                                if (lhs.top() != rhs.top())
                                        return false;
                                lhs.pop();
                                rhs.pop();
                        }
                        return true;
                }

                TEST_METHOD(CheckShortestPath)
                {
                        Graph graph(8);
                        graph.addEdge(Edge(0, 1));
                        graph.addEdge(Edge(0, 4));
                        graph.addEdge(Edge(0, 7));
                        graph.addEdge(Edge(1, 2));
                        graph.addEdge(Edge(1, 3));
                        graph.addEdge(Edge(1, 7));
                        graph.addEdge(Edge(2, 3));
                        graph.addEdge(Edge(2, 6));
                        graph.addEdge(Edge(3, 6));
                        graph.addEdge(Edge(4, 5));
                        graph.addEdge(Edge(4, 6));
                        graph.addEdge(Edge(4, 7));
                        graph.addEdge(Edge(5, 2));
                        graph.addEdge(Edge(5, 6));
                        graph.addEdge(Edge(7, 5));
                        graph.addEdge(Edge(7, 2));

                        DijkstraSP DSP(graph, 0);
                        Assert::AreEqual(0, DSP.distTo(0));
                        Assert::AreEqual(1, DSP.distTo(1));
                        Assert::AreEqual(2, DSP.distTo(2));
                        Assert::AreEqual(2, DSP.distTo(3));
                        Assert::AreEqual(1, DSP.distTo(4));
                        Assert::AreEqual(2, DSP.distTo(5));
                        Assert::AreEqual(2, DSP.distTo(6));
                        Assert::AreEqual(1, DSP.distTo(7));

                        Assert::IsTrue(DSP.hasPathTo(0));
                        Assert::IsTrue(DSP.hasPathTo(1));
                        Assert::IsTrue(DSP.hasPathTo(2));
                        Assert::IsTrue(DSP.hasPathTo(3));
                        Assert::IsTrue(DSP.hasPathTo(4));
                        Assert::IsTrue(DSP.hasPathTo(5));
                        Assert::IsTrue(DSP.hasPathTo(6));
                        Assert::IsTrue(DSP.hasPathTo(7));

                        DijkstraSP::PathToStack etalon;
                        etalon.push(3);
                        etalon.push(1);
                        etalon.push(0);
                        DijkstraSP::PathToStack actual = DSP.pathTo(3);
                        Assert::IsTrue(equalStacks(etalon, actual));

                        DijkstraSP::PathToStack etalon2;
                        etalon2.push(6);
                        etalon2.push(4);
                        etalon2.push(0);
                        DijkstraSP::PathToStack actual2 = DSP.pathTo(6);
                        Assert::IsTrue(equalStacks(etalon2, actual2));

                        DijkstraSP::PathToStack etalon3;
                        etalon3.push(7);
                        etalon3.push(0);
                        DijkstraSP::PathToStack actual3 = DSP.pathTo(7);
                        Assert::IsTrue(equalStacks(etalon3, actual3));

                        DijkstraSP::PathToStack etalon4;
                        etalon4.push(1);
                        etalon4.push(0);
                        DijkstraSP::PathToStack actual4 = DSP.pathTo(1);
                        Assert::IsTrue(equalStacks(etalon4, actual4));
                }

        };
}