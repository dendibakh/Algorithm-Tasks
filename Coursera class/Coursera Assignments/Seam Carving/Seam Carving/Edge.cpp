#include "Edge.h"
#include <sstream>

Edge::Edge(int v, int w, double weight) : v(v), w(w), weight(weight)
{
}

bool Edge::operator == (const Edge& rhs) const
{
	return v == rhs.v && w == rhs.w && weight == rhs.weight;
}

bool Edge::operator<(const Edge& rhs) const
{
	return weight < rhs.weight;
}

bool Edge::operator>(const Edge& rhs) const
{
	return !this->operator<(rhs) && !this->operator==(rhs);
}

int Edge::from() const
{
	return v;
}

int Edge::to() const
{
	return w;
}

double Edge::getWeight() const
{
	return weight;
}


std::string Edge::toString() const
{
	std::stringstream stream;
	stream << v << " - " << w << " " << weight;
	return stream.str();
}