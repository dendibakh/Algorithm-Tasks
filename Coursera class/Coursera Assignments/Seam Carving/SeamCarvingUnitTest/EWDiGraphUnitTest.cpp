#include "stdafx.h"
#include "EWDiGraph.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace EWGraphUnitTest
{
   [TestClass]
   public ref class EWDiGraphUnitTest
   {
   public:

      [TestMethod]
      void CheckConstruct()
      {
         EWDiGraph graph(10);
      }

      [TestMethod]
      void CheckConstructInWork()
      {
         EWDiGraph graph(2);
         Assert::AreEqual(graph.getVertexCount(), 2);
         const EWDiGraph::EdgesList& list = graph.getAdjacentVertex(1);
         Assert::IsTrue(list.empty());
      }

      [TestMethod]
      void CheckAddEdge()
      {
         EWDiGraph graph(2);
         graph.addEdge(Edge(0, 1, 0.22));
         const EWDiGraph::EdgesList& list0 = graph.getAdjacentVertex(0);
         Assert::AreEqual(int(list0.size()), 1);
         int v = list0.front().from();
         int w = list0.front().to();
         Assert::AreEqual(v, 0);
         Assert::AreEqual(w, 1);
         Assert::AreEqual(list0.front().getWeight(), 0.22);

         const EWDiGraph::EdgesList& list1 = graph.getAdjacentVertex(1);
         Assert::IsTrue(list1.empty());
      }

      [TestMethod]
      void CheckAddWrongEdge()
      {
         EWDiGraph graph(2);
         try
         {
            graph.addEdge(Edge(0, 3, 0.44));
            Assert::Fail(L"There must be exception");
         }
         catch (std::exception&)
         {
         }
      }

      [TestMethod]
      void CheckAddMoreEdge()
      {
         EWDiGraph graph(5);
         graph.addEdge(Edge(0, 1, 0.5));
         graph.addEdge(Edge(0, 2, 0.5));
         graph.addEdge(Edge(1, 2, 0.5));
         graph.addEdge(Edge(2, 3, 0.5));
         graph.addEdge(Edge(3, 4, 0.5));
         graph.addEdge(Edge(2, 4, 0.5));

         EWDiGraph::EdgesList expected1;
         expected1.push_front(Edge(1, 2, 0.5));
         const EWDiGraph::EdgesList& list1 = graph.getAdjacentVertex(1);
         Assert::IsTrue(std::equal(list1.begin(), list1.end(), expected1.begin()));

         EWDiGraph::EdgesList expected2;
         expected2.push_front(Edge(2, 4, 0.5));
         expected2.push_front(Edge(2, 3, 0.5));
         const EWDiGraph::EdgesList& list2 = graph.getAdjacentVertex(2);
         Assert::IsTrue(std::equal(list2.begin(), list2.end(), expected2.begin()));

         const EWDiGraph::EdgesList& list4 = graph.getAdjacentVertex(4);
         Assert::IsTrue(list4.empty());
      }

      [TestMethod]
      void CheckGetWrongAdjacentVertex()
      {
         EWDiGraph graph(5);
         graph.addEdge(Edge(0, 1, 0.5));
         graph.addEdge(Edge(0, 4, 0.5));

         try
         {
            const EWDiGraph::EdgesList& list10 = graph.getAdjacentVertex(10);
            Assert::Fail(L"There must be exception");
         }
         catch (std::exception&)
         {
         }
      }

      [TestMethod]
      void CheckCounts()
      {
         EWDiGraph graph(5);
         graph.addEdge(Edge(0, 1, 0.5));
         graph.addEdge(Edge(0, 2, 0.5));
         graph.addEdge(Edge(1, 2, 0.5));
         graph.addEdge(Edge(2, 3, 0.5));
         graph.addEdge(Edge(3, 4, 0.5));
         graph.addEdge(Edge(2, 4, 0.5));

         Assert::AreEqual(graph.getEdgesCount(), 6);
         Assert::AreEqual(graph.getVertexCount(), 5);
      }

      [TestMethod]
      void CheckCounts2()
      {
         EWDiGraph graph(5);
         graph.addEdge(Edge(0, 1, 0.5));
         graph.addEdge(Edge(0, 2, 0.5));
         graph.addEdge(Edge(0, 2, 0.5));
         graph.addEdge(Edge(1, 2, 0.5));
         graph.addEdge(Edge(2, 3, 0.5));
         graph.addEdge(Edge(3, 4, 0.5));
         graph.addEdge(Edge(3, 4, 0.5));
         graph.addEdge(Edge(2, 4, 0.5));

         Assert::AreEqual(graph.getEdgesCount(), 6);
         Assert::AreEqual(graph.getVertexCount(), 5);
      }

      [TestMethod]
      void ChecktoString()
      {
         EWDiGraph graph(5);
         graph.addEdge(Edge(0, 1, 0.5));
         graph.addEdge(Edge(0, 2, 0.5));
         graph.addEdge(Edge(1, 2, 0.5));
         graph.addEdge(Edge(2, 3, 0.5));
         graph.addEdge(Edge(3, 4, 0.5));
         graph.addEdge(Edge(2, 4, 0.5));

         Assert::IsTrue(graph.toString() == std::string("0 - 1 0.5\n0 - 2 0.5\n1 - 2 0.5\n2 - 3 0.5\n2 - 4 0.5\n3 - 4 0.5\n"));
      }
   };
}