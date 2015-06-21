#pragma once
#include <list>
#include <string>
#include <vector>

class DiGraph
{
	void checkVertex(int v) const;
	bool alreadyConnected(int v, int w) const;
public:
	typedef std::list<int> EdgesList;
	DiGraph(int N);
	DiGraph(const DiGraph& rhs) = default;
	DiGraph& operator=(const DiGraph& rhs) = default;
	bool operator==(const DiGraph& rhs);
	void addEdge(int v, int w);
	EdgesList getAdjacentVertex(int v) const;
	int getVertexCount() const;
	int getEdgesCount() const;
	std::string toString() const;
	int degree(int v) const;
	int maxdegree() const;
	double averagedegree() const;
	int numberOfSelfLoops() const;
	DiGraph getReversed() const;
private:
	const int N;
	std::vector<EdgesList> vertecies;
};