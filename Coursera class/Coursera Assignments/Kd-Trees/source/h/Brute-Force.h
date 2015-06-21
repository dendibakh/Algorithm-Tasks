#pragma once

#include "RecHV.h"
#include <set>
#include <list>

namespace BruteForce
{
   class PointSET
   {
      public:
         PointSET();
         bool isEmpty() const;
         size_t size() const;
         void insert(const Point& p);                      // add the point p to the set (if it is not already in the set)
         bool contains(const Point& p) const;              // does the set contain the point p?
         std::list<Point> range(const RectHV& rect) const; // all points in the set that are inside the rectangle
         Point nearest(const Point& p) const;              // a nearest neighbor in the set to p
      private:
         std::set<Point> storage;
   };
}