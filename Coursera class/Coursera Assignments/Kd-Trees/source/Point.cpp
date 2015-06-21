#include "Point.h"
#include <sstream>
#include <cmath>

Point::Point() : x(0), y(0)
{
   
}

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

Point& Point::operator=(const Point& rhs)
{
   this->x = rhs.x;
   this->y = rhs.y;
   return *this;
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

std::string Point::toString() const
{
   std::stringstream stream;
   stream << "Point (" << x << ";" << y << ")";
   return stream.str();
}

double Point::distanceTo(const Point& p) const
{
   int deltaX = this->x - p.getX();
   int deltaY = this->y - p.getY();
   return sqrt(double(deltaX * deltaX + deltaY * deltaY));
}

double Point::distanceSquaredTo(const Point& p) const
{
   int deltaX = this->x - p.getX();
   int deltaY = this->y - p.getY();
   return deltaX * deltaX + deltaY * deltaY;
}