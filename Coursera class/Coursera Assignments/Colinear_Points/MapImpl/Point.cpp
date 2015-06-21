#include "Point.h"

Point::Point(int x, int y) : x(x), y(y)
{
   
}

Point::Point(const Point& rhs) : x(rhs.x), y(rhs.y)
{
   
}

int Point::getX() const
{
   return this->x;
}

int Point::getY() const
{
   return this->y;
}

void Point::operator=(const Point& rhs)
{
   this->x = rhs.x;
   this->y = rhs.y;
}

bool Point::operator==(const Point& rhs) const
{
   return (rhs.y == this->y) && (rhs.x == this->x);
}

bool Point::operator<(const Point& rhs) const
{
   if (rhs.y > this->y)
      return true;
   else if (rhs.y == this->y)
      if (rhs.x > this->x)
         return true;
   return false;
}