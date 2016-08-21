#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

class Graph {
  bool alreadyConnected(char v, char w);

public:
  typedef std::list<char> EdgesList;
  Graph();
  void addEdge(char v, char w);
  EdgesList getAdjacentVertex(char v);
  int getVertexCount() const;
  int getEdgesCount() const;
  std::string toString() const;
  int degree(char v);
  int maxdegree() const;
  // private:
public:
  std::map<char, EdgesList> vertecies;
};

Graph::Graph() {}

void Graph::addEdge(char v, char w) {
  if (!alreadyConnected(v, w))
    vertecies[v].push_back(w);
  else
    throw std::runtime_error("E2");
}

Graph::EdgesList Graph::getAdjacentVertex(char v) { return vertecies[v]; }

int Graph::getVertexCount() const { return vertecies.size(); }

int Graph::getEdgesCount() const {
  int retVal = 0;
  for (auto i = vertecies.begin(); i != vertecies.end(); ++i) {
    retVal += i->second.size();
  }
  return retVal;
}

bool Graph::alreadyConnected(char v, char w) {
  for (auto i = vertecies[v].begin(); i != vertecies[v].end(); ++i) {
    if (*i == w)
      return true;
  }
  return false;
}

std::string Graph::toString() const {
  std::string retVal;
  for (auto i = vertecies.begin(); i != vertecies.end(); ++i) {
    char v = i->first;
    for (auto j = i->second.begin(); j != i->second.end(); ++j) {
      std::stringstream stream;
      stream << "(" << v << "," << *j << ")	";
      retVal += stream.str();
    }
  }
  return retVal;
}

int Graph::degree(char v) { return vertecies[v].size(); }

int Graph::maxdegree() const {
  size_t retVal = 0;
  for (auto i = vertecies.begin(); i != vertecies.end(); ++i) {
    retVal = std::max(retVal, i->second.size());
  }
  return retVal;
}
class TopologicalSort {
  void dfs(Graph &graph, char v);

public:
  typedef std::stack<char> PostOrderContainer;
  TopologicalSort(Graph &graph);
  PostOrderContainer getPostOrder();

private:
  Graph &graph;
  std::vector<bool> marked;
  PostOrderContainer PostOrder;
};

void TopologicalSort::dfs(Graph &graph, char v) {
  marked[v] = true;
  auto list = graph.getAdjacentVertex(v);
  for (auto i = list.begin(); i != list.end(); ++i) {
    if (!marked[*i])
      dfs(graph, *i);
  }
  PostOrder.push(v);
}

TopologicalSort::TopologicalSort(Graph &graph)
    : graph(graph), marked(graph.getVertexCount(), false) {
  for (auto &i : graph.vertecies) {
    if (!marked[i.first])
      dfs(graph, i.first);
  }
}

TopologicalSort::PostOrderContainer TopologicalSort::getPostOrder() {
  return PostOrder;
}

Graph constructGraph(const std::string &graphStr) {
  if (graphStr.empty())
    throw std::runtime_error("E1");
  if (graphStr[0] != '(')
    throw std::runtime_error("E1");
  if (graphStr[graphStr.size() - 1] != ')')
    throw std::runtime_error("E1");
  Graph graph;
  auto it = graphStr.begin();
  while (it != graphStr.end()) {
    it = std::find(it, graphStr.end(), '(');
    if (it != graphStr.end()) {
      ++it;
      if (it == graphStr.end())
        throw std::runtime_error("E1");
      char parent = *it;
      if (parent < 0x41 || parent > 0x5A)
        throw std::runtime_error("E1");
      ++it;
      if (it == graphStr.end())
        throw std::runtime_error("E1");
      if (*it != ',')
        throw std::runtime_error("E1");
      ++it;
      if (it == graphStr.end())
        throw std::runtime_error("E1");
      char child = *it;
      if (child < 0x41 || child > 0x5A)
        throw std::runtime_error("E1");
      ++it;
      if (it == graphStr.end())
        throw std::runtime_error("E1");
      if (*it != ')')
        throw std::runtime_error("E1");
      graph.addEdge(parent, child);

      ++it;
      if (it == graphStr.end())
        return graph;
      else if (*it != '	')
        throw std::runtime_error("E1");
    }
  }
  return graph;
}

using namespace std;

int main() {
  std::string graphStr;
  std::getline(std::cin, graphStr);
  try {
    // std::cout	<<	graphStr	<<	"\n";
    auto graph = constructGraph(graphStr);
    // std::cout	<<	graph.toString();
    if (graph.maxdegree() > 2) {
      std::cout << "E3";
      return 1;
    }

    // std::cout	<<	"\n";

    TopologicalSort tpSort(graph);
    auto topologicalOrder = tpSort.getPostOrder();

    std::cout << topologicalOrder.size() << "\n";
    while (!topologicalOrder.empty()) {
      auto t = topologicalOrder.top();
      topologicalOrder.pop();
      std::cout << t << "<-";
    }
    std::cout << "\n";

    //	further:
    //	idea	is	to	run	dfs	once
    // again	in	a	topological	order.
    //	Using	this	order	I	will	visit
    // every	vertex	only	once.	If	not
    //-	it	is	a	violation	of	E4.
    //
  } catch (std::exception &e) {
    std::cout << e.what();
  }
  return 0;
}
