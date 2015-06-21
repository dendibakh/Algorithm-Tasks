#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GrUnitTest
{               
        TEST_CLASS(GraphUnitTest)
        {
        public:
                
                TEST_METHOD(CheckConstruct)
                {
                        Graph graph(10);
                }

                TEST_METHOD(CheckConstructInWork)
                {
                        Graph graph(2);
                        Assert::AreEqual(graph.getVertexCount(), 2);
                        Graph::EdgesList list = graph.getAdjacentVertex(1);
                        Assert::IsTrue(list.empty());
                }

                TEST_METHOD(CheckAddEdge)
                {
                        Graph graph(2);
                        graph.addEdge(Edge(0, 1));
                        Graph::EdgesList list0 = graph.getAdjacentVertex(0);
                        Assert::AreEqual(int(list0.size()), 1);
                        int v = list0.front().from();
                        int w = list0.front().to();
                        Assert::AreEqual(v, 0);
                        Assert::AreEqual(w, 1);

                        Graph::EdgesList list1 = graph.getAdjacentVertex(1);
                        Assert::AreEqual(int(list1.size()), 1);
                        int v1 = list1.front().from();
                        int w1 = list1.front().to();
                        Assert::AreEqual(v1, 1);
                        Assert::AreEqual(w1, 0);
                }
                
                TEST_METHOD(CheckAddWrongEdge)
                {
                        Graph graph(2);
                        try
                        {
                                graph.addEdge(Edge(0, 3));
                                Assert::Fail(L"There must be exception");
                        }
                        catch (std::exception&)
                        {
                        }
                }

                TEST_METHOD(CheckAddMoreEdge)
                {
                        Graph graph(5);
                        graph.addEdge(Edge(0, 1));
                        graph.addEdge(Edge(0, 2));
                        graph.addEdge(Edge(1, 2));
                        graph.addEdge(Edge(2, 3));
                        graph.addEdge(Edge(3, 4));
                        graph.addEdge(Edge(2, 4));

                        Graph::EdgesList expected1;
                        expected1.push_front(Edge(1, 2));
                        expected1.push_front(Edge(1, 0));
                        Graph::EdgesList list1 = graph.getAdjacentVertex(1);
                        Assert::IsTrue(std::equal(list1.begin(), list1.end(), expected1.begin()));

                        Graph::EdgesList expected2;
                        expected2.push_front(Edge(2, 4));
                        expected2.push_front(Edge(2, 3));
                        expected2.push_front(Edge(2, 1));
                        expected2.push_front(Edge(2, 0));
                        Graph::EdgesList list2 = graph.getAdjacentVertex(2);
                        Assert::IsTrue(std::equal(list2.begin(), list2.end(), expected2.begin()));

                        Graph::EdgesList expected4;
                        expected4.push_front(Edge(4, 2));
                        expected4.push_front(Edge(4, 3));
                        Graph::EdgesList list4 = graph.getAdjacentVertex(4);
                        Assert::IsTrue(std::equal(list4.begin(), list4.end(), expected4.begin()));
                }

                TEST_METHOD(CheckGetWrongAdjacentVertex)
                {
                        Graph graph(5);
                        graph.addEdge(Edge(0, 1));
                        graph.addEdge(Edge(0, 4));

                        try
                        {
                                Graph::EdgesList list10 = graph.getAdjacentVertex(10);
                                Assert::Fail(L"There must be exception");
                        }
                        catch (std::exception&)
                        {
                        }
                }
                
                TEST_METHOD(CheckCounts)
                {
                        Graph graph(5);
                        graph.addEdge(Edge(0, 1));
                        graph.addEdge(Edge(0, 2));
                        graph.addEdge(Edge(1, 2));
                        graph.addEdge(Edge(2, 3));
                        graph.addEdge(Edge(3, 4));
                        graph.addEdge(Edge(2, 4));

                        Assert::AreEqual(graph.getEdgesCount(), 6);
                        Assert::AreEqual(graph.getVertexCount(), 5);
                }
                
                TEST_METHOD(CheckCounts2)
                {
                        Graph graph(5);
                        graph.addEdge(Edge(0, 1));
                        graph.addEdge(Edge(0, 2));
                        graph.addEdge(Edge(0, 2));
                        graph.addEdge(Edge(1, 2));
                        graph.addEdge(Edge(2, 3));
                        graph.addEdge(Edge(3, 4));
                        graph.addEdge(Edge(3, 4));
                        graph.addEdge(Edge(2, 4));

                        Assert::AreEqual(graph.getEdgesCount(), 6);
                        Assert::AreEqual(graph.getVertexCount(), 5);
                }
                
                TEST_METHOD(ChecktoString)
                {
                        Graph graph(5);
                        graph.addEdge(Edge(0, 1));
                        graph.addEdge(Edge(0, 2));
                        graph.addEdge(Edge(1, 2));
                        graph.addEdge(Edge(2, 3));
                        graph.addEdge(Edge(3, 4));
                        graph.addEdge(Edge(2, 4));

                        Assert::IsTrue(graph.toString() == std::string("0 - 1\n0 - 2\n1 - 2\n2 - 3\n2 - 4\n3 - 4\n"));
                }
        };
}