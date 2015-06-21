#pragma once
#include <string>

class FlowEdge
{
public:
	FlowEdge(int v, int w, int capacity);
	FlowEdge(const FlowEdge& rhs) = default;
	FlowEdge& operator=(const FlowEdge& rhs) = default;
	bool operator==(const FlowEdge& rhs) const;
	bool operator<(const FlowEdge& rhs) const;
	bool operator>(const FlowEdge& rhs) const;

	int from() const;
	int to() const;
	int other(int v) const;

	int getFlow() const;
	int getCapacity() const;
	int getResidualCapacityTo(int v) const;
	void addResidualFlowTo(int v, int delta);

	std::string toString() const;

private:
	int v;
	int w;
	int capacity;
	int flow;
};