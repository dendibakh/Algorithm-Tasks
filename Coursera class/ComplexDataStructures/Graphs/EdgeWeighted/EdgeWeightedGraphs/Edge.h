#pragma once
#include <string>

class Edge
{
public:
	Edge();
	Edge(int v, int w, double weight);
	Edge(const Edge& rhs) = default;
	Edge& operator=(const Edge& rhs) = default;
	bool operator==(const Edge& rhs) const;
	bool operator<(const Edge& rhs) const;
	bool operator>(const Edge& rhs) const;

	int either() const;
	int other(int v) const;
	double getWeight() const;

	std::string toString() const;

private:
	int v;
	int w;
	double weight;
};