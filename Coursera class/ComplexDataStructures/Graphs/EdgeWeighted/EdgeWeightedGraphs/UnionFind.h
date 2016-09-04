#pragma once
#include <vector>

class UnionFind
{
	void checkIndex(int v) const;
public:
	UnionFind(int N);

	// Return the number of disjoint sets.
	int getCount() const;
	
	// Return component identifier for component containing p
	int find(int p) const;

	// Are objects p and q in the same set?
	bool connected(int p, int q) const;
	
	// Replace sets containing p and q with their union.
	void unionElems(int p, int q);
private:
	std::vector<int> id;    // id[i] = parent of i
	std::vector<int> sz;    // sz[i] = number of objects in subtree rooted at i
	int count;   // number of components
	const int size;   // initial size
};
