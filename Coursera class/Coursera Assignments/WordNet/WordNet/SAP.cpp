#include "SAP.h"
#include "bfs.h"
#include <stack>

using namespace TpgSort;
using namespace std;

SAP::SAP(const DiGraph& graph) : graph(graph)
{
   // running time = O(E+V).
   TopologicalSort tpgSrt(graph);
   TopologicalSort::ReversePostOrderContainer rPostOrder = tpgSrt.getReversePostOrder();
   while(!rPostOrder.empty())
   {
      revPostOrder.push_back(rPostOrder.front());
      rPostOrder.pop();
   }
}

void SAP::checkVertex(int v) const
{
   if ((v < 0) || v >= graph.getVertexCount())
      throw std::runtime_error("Invalid vertex");
}

CommonAncestor SAP::findClosestAncestor(int v, int w)
{
   checkVertex(v);
   checkVertex(w);
   CommonAncestor retVal = {-1, -1};
   bfs::Paths<DiGraph> pathsV(graph, v); // running time = O(E+V).
   bfs::Paths<DiGraph> pathsW(graph, w); // running time = O(E+V).
   stack<int> ancestors;   
   for (auto i = revPostOrder.begin(); i != revPostOrder.end(); ++i)
   {
      int curAncestor = *i;
      ancestors.push(curAncestor);
      if ( (curAncestor == v) || (curAncestor == w) )
         break;
   }
   while (!ancestors.empty()) // running time = O(E).
   {
      int curAncestor = ancestors.top();
      if (pathsV.hasPathTo(curAncestor) && pathsW.hasPathTo(curAncestor))
      {
         int curDistanceToAncestor = pathsV.distanceTo(curAncestor) + pathsW.distanceTo(curAncestor);
         if ((curDistanceToAncestor < retVal.lenght) || (-1 == retVal.lenght))
         {
            retVal.ancestorID = curAncestor;
            retVal.lenght = curDistanceToAncestor;
         }
      }
      ancestors.pop();
   }
   return retVal;
}

CommonAncestor SAP::findClosestAncestorFromTwoLists(const list<int>& v, const list<int>& w)
{
   // running time = O( N * M * (5*E + 3*V) ), N = v.size(); M = w.size().
   CommonAncestor minDistAncestor = {-1, -1};
   for (list<int>::const_iterator i = v.begin(); i != v.end(); ++i)
   {
      checkVertex(*i);
      for (list<int>::const_iterator j = w.begin(); j != w.end(); ++j)
      {
         checkVertex(*j);
         CommonAncestor curAncestor = findClosestAncestor(*i, *j);
         if ( (-1 == minDistAncestor.lenght) || (curAncestor.lenght < minDistAncestor.lenght ))
            minDistAncestor = curAncestor;
      }
   }
   return minDistAncestor;
}