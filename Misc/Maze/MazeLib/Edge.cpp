#include "Edge.h"
#include <sstream>

Edge::Edge(int v, int w) : v(v), w(w)
{
}

bool Edge::operator == (const Edge& rhs) const
{
        return v == rhs.v && w == rhs.w;
}

int Edge::from() const
{
        return v;
}

int Edge::to() const
{
        return w;
}

std::string Edge::toString() const
{
        std::stringstream stream;
        stream << v << " - " << w;
        return stream.str();
}