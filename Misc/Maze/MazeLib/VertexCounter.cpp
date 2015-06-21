#include "VertexCounter.h"
#include <algorithm>

VertexCounter::VertexCounter(const Graph& graph, const std::vector<bool>& marked, int source, int destination) : graph(graph), marked(marked), count(0), destination(destination)
{
   if ((source < 0) || source >= graph.getVertexCount())
      throw std::runtime_error("Invalid source vertex");
   dfs(source);
}

void VertexCounter::dfs(int v)
{
   ++count;
   marked[v] = true;
   auto list = graph.getAdjacentVertex(v);
   for (auto i = list.begin(); i != list.end(); ++i)
   {
      int w = i->to();
      if (!marked[w])
      {
         if (w != destination) // if we found destination vertex, there is no need to recursively visit it, because it's the last vertex in the path
         {
            dfs(w);
         }
         else
         {
            marked[destination] = true;
            ++count;
         }
      }
   }
}

int VertexCounter::getCount() const
{
   return count;
}

bool VertexCounter::destinationIsReachable() const
{
   return marked[destination];
}