#pragma once

class Point
{
   public:
      Point();
      Point(int x, int y);
      Point(const Point& rhs);
      int getX() const;
      int getY() const;
      void operator=(const Point& rhs);
      bool operator==(const Point& rhs) const;
      bool operator<(const Point& rhs) const;
      int hashCode() const;
      int hashCode();
      static int maxHashCode();
   private:
      int x;
      int y;
};