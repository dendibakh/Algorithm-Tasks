#include "UnionFind.h"

UnionFind::UnionFind(int N) : count(N), size(N), id(N), sz(N)
{
	for (int i = 0; i < N; i++) 
	{
		id[i] = i;
		sz[i] = 1;
	}
}

void UnionFind::checkIndex(int v) const
{
	if ((v < 0) || (v >= size))
		throw std::runtime_error("Invalid index");
}

int UnionFind::getCount() const
{
	return count;
}

int UnionFind::find(int p) const
{
	checkIndex(p);
	while (p != id[p])
		p = id[p];
	return p;
}

bool UnionFind::connected(int p, int q) const
{
	checkIndex(p);
	checkIndex(q);
	return find(p) == find(q);
}

void UnionFind::unionElems(int p, int q)
{
	checkIndex(p);
	checkIndex(q);
	int i = find(p);
	int j = find(q);
	if (i == j) 
		return;

	// make smaller root point to larger one
	if (sz[i] < sz[j]) 
	{ 
		id[i] = j; 
		sz[j] += sz[i]; 
	}
	else               
	{ 
		id[j] = i; 
		sz[i] += sz[j]; 
	}
	count--;
}

