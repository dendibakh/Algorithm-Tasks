#pragma once

class Point
{
   public:
      Point(int x, int y);
      Point(const Point& rhs);
      int getX() const;
      int getY() const;
      void operator=(const Point& rhs);
      bool operator==(const Point& rhs) const;
      bool operator<(const Point& rhs) const;
   private:
      int x;
      int y;
};