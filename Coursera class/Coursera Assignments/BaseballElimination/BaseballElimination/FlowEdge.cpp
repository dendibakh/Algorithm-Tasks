#include "FlowEdge.h"
#include <sstream>

FlowEdge::FlowEdge(int v, int w, int capacity) : v(v), w(w), capacity(capacity), flow(0)
{
}

bool FlowEdge::operator == (const FlowEdge& rhs) const
{
	return v == rhs.v && w == rhs.w && capacity == rhs.capacity && flow == rhs.flow;
}

bool FlowEdge::operator<(const FlowEdge& rhs) const
{
	return capacity < rhs.capacity;
}

bool FlowEdge::operator>(const FlowEdge& rhs) const
{
	return !this->operator<(rhs) && !this->operator==(rhs);
}

int FlowEdge::from() const
{
	return v;
}

int FlowEdge::to() const
{
	return w;
}

int FlowEdge::other(int v) const
{
	if (v == this->v)
		return this->w;
	return this->v;
}

int FlowEdge::getFlow() const
{
	return flow;
}

int FlowEdge::getCapacity() const
{
	return capacity;
}

int FlowEdge::getResidualCapacityTo(int v) const
{
	if (v == this->v)
		return flow;
	if (v == this->w)
		return capacity - flow;
	throw std::runtime_error("No such vertex in this edge");
}

void FlowEdge::addResidualFlowTo(int v, int delta)
{
	if (v == this->v)
		flow -= delta;
	else if (v == this->w)
		flow += delta;
	else
		throw std::runtime_error("No such vertex in this edge");
}

std::string FlowEdge::toString() const
{
	std::stringstream stream;
	stream << v << " - " << w << " " << flow << "/" << capacity;
	return stream.str();
}