#pragma once
#include <stack>
#include <queue>

// running time = O(E+V).

namespace bfs
{
   template <class GraphType>
   class Paths
   {
      static const int nullValue = -1;

      void bfs(const GraphType& graph, int v)
      {
         std::queue<int> vertecies;
         vertecies.push(v);
         distTo[v] = 0;
         while (!vertecies.empty())
         {
            int current = vertecies.front();
            vertecies.pop();
            GraphType::EdgesList list = graph.getAdjacentVertex(current);
            for (auto i = list.begin(); i != list.end(); ++i)
            {
               int adjacent = *i;
               if (nullValue == distTo[adjacent])
               {
                  vertecies.push(adjacent);
                  edgeTo[adjacent] = current;
                  distTo[adjacent] = distTo[current] + 1;
               }
            }
         }
      }

   public:
      typedef std::stack<int> VertexStack;

      Paths(const GraphType& graph, int source) : graph(graph), source(source),
         edgeTo(graph.getVertexCount(), nullValue), distTo(graph.getVertexCount(), nullValue)
      {
         if ((source < 0) || source >= graph.getVertexCount())
            throw std::runtime_error("Invalid source vertex");
         bfs(graph, source);
      }

      bool hasPathTo(int v) const
      {
         return nullValue != distTo[v];
      }

      VertexStack pathTo(int v) const
      {
         VertexStack st;
         if (!hasPathTo(v))
            return st;
         for (int i = v; i != source; i = edgeTo[i])
         {
            st.push(i);
         }
         st.push(source);
         return st;
      }

      int distanceTo(int v) const
      {
         if (nullValue == distTo[v])
            throw std::runtime_error("There is no path to that vertex");
         return distTo[v];
      }
   private:
      const GraphType& graph;
      const int source;
      std::vector<int> edgeTo;
      std::vector<int> distTo;
   };
}