#pragma once
#include "Point.h"

class RectHV
{
   public:
      RectHV(int x1, int y1, int x2, int y2);
      RectHV(const RectHV& rhs);
      int getX1() const;
      int getX2() const;
      int getY1() const;
      int getY2() const;
      RectHV& operator=(const RectHV& rhs);
      bool operator==(const RectHV& rhs) const;
      std::string toString() const;

      bool contains(const Point& p) const;              // does this rectangle contain the point p (either inside or on boundary)?
      bool intersects(const RectHV& rhs) const;         // does this rectangle intersect that rectangle (at one or more points)?
      double distanceTo(const Point& p) const;          // Euclidean distance from point p to the closest point in rectangle
      double distanceSquaredTo(const Point& p) const;   // square of Euclidean distance from point p to closest point in rectangle

   private:
      int x1;
      int x2;
      int y1;
      int y2;
};