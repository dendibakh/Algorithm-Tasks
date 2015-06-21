#pragma once
#include <string>

class Edge
{
public:
        Edge(int v, int w);
        Edge(const Edge& rhs) = default;
        Edge& operator=(const Edge& rhs) = default;
        bool operator==(const Edge& rhs) const;

        int from() const;
        int to() const;

        std::string toString() const;

private:
        int v;
        int w;
};