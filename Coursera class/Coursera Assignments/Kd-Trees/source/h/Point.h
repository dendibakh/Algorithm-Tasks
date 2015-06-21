#pragma once
#include <string>

class Point
{
   public:
      Point();
      Point(int x, int y);
      Point(const Point& rhs);
      int getX() const;
      int getY() const;
      Point& operator=(const Point& rhs);
      bool operator==(const Point& rhs) const;
      bool operator<(const Point& rhs) const;
      std::string toString() const;

      double distanceTo(const Point& p) const;        // Euclidean distance between two points
      double distanceSquaredTo(const Point& p) const; // square of Euclidean distance between two points
   private:
      int x;
      int y;
};