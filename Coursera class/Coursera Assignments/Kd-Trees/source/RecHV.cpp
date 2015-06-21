#include "RecHV.h"
#include <sstream>

RectHV::RectHV(int x1, int y1, int x2, int y2) : x1(x1), x2(x2), y1(y1), y2(y2)
{
   if ((x1 == x2) || (y1 == y2))
      throw std::runtime_error("Invalid rectangle");
}

RectHV::RectHV(const RectHV& rhs) : x1(rhs.x1), x2(rhs.x2), y1(rhs.y1), y2(rhs.y2)
{

}

int RectHV::getX1() const
{
   return x1;
}

int RectHV::getX2() const
{
   return x2;
}

int RectHV::getY1() const
{
   return y1;
}

int RectHV::getY2() const
{
   return y2;
}

RectHV& RectHV::operator=(const RectHV& rhs)
{
   this->x1 = rhs.x1;
   this->x2 = rhs.x2;
   this->y1 = rhs.y1;
   this->y2 = rhs.y2;
   return *this;
}

bool RectHV::operator==(const RectHV& rhs) const
{
   return this->x1 == rhs.x1 && this->x2 == rhs.x2 && this->y1 == rhs.y1 && this->y2 == rhs.y2;
}

std::string RectHV::toString() const
{
   std::stringstream stream;
   stream << "Rectangle (" << x1 << ";" << y1 << ") - (" << x2 << ";" << y2 << ")";
   return stream.str();
}

bool RectHV::contains(const Point& p) const
{
   return p.getX() >= this->getX1() && p.getX() <= this->getX2() && p.getY() >= this->getY1() && p.getY() <= this->getY2();
}

bool RectHV::intersects(const RectHV& rhs) const
{
   // Любая из границ прямоугольника лежит между границ другого прямоугольника.
   bool Xintersection = rhs.getX1() >= this->getX1() && rhs.getX1() <= this->getX2() || rhs.getX2() >= this->getX1() && rhs.getX2() <= this->getX2() ||
                        this->getX1() >= rhs.getX1() && this->getX1() <= rhs.getX2() || this->getX2() >= rhs.getX1() && this->getX2() <= rhs.getX2();
   bool Yintersection = rhs.getY1() >= this->getY1() && rhs.getY1() <= this->getY2() || rhs.getY2() >= this->getY1() && rhs.getY2() <= this->getY2() ||
                        this->getY1() >= rhs.getY1() && this->getY1() <= rhs.getY2() || this->getY2() >= rhs.getY1() && this->getY2() <= rhs.getY2();
   return Xintersection && Yintersection;
}

double RectHV::distanceTo(const Point& p) const
{
   // Если внутри, то дистанция нулевая.
   if (contains(p))
      return 0.0;
   // Пробуем опустить перпендикуляр.
   if ((p.getX() >= this->getX1()) && (p.getX() <= this->getX2()))
      return std::min(abs(this->getY1() - p.getY()), abs(this->getY2() - p.getY()));
   if ((p.getY() >= this->getY1()) && (p.getY() <= this->getY2()))
      return std::min(abs(this->getX1() - p.getX()), abs(this->getX2() - p.getX()));
   // Иначе определяем наименьшее растояние до вершин прямоугольника.
   double distance1 = p.distanceTo(Point(this->getX1(), this->getY1()));
   double distance2 = p.distanceTo(Point(this->getX1(), this->getY2()));
   double distance3 = p.distanceTo(Point(this->getX2(), this->getY1()));
   double distance4 = p.distanceTo(Point(this->getX2(), this->getY2()));
   return std::min( std::min(distance1, distance2), std::min(distance3, distance4) );
}

double RectHV::distanceSquaredTo(const Point& p) const
{
   // Если внутри, то дистанция нулевая.
   if (contains(p))
      return 0.0;
   // Пробуем опустить перпендикуляр.
   if ((p.getX() >= this->getX1()) && (p.getX() <= this->getX2()))
   {
      double distance = std::min(abs(this->getY1() - p.getY()), abs(this->getY2() - p.getY()));
      return distance * distance;
   }
   if ((p.getY() >= this->getY1()) && (p.getY() <= this->getY2()))
   {
      double distance = std::min(abs(this->getX1() - p.getX()), abs(this->getX2() - p.getX()));
      return distance * distance;
   }
   // Иначе определяем наименьшее растояние до вершин прямоугольника.
   double distance1 = p.distanceSquaredTo(Point(this->getX1(), this->getY1()));
   double distance2 = p.distanceSquaredTo(Point(this->getX1(), this->getY2()));
   double distance3 = p.distanceSquaredTo(Point(this->getX2(), this->getY1()));
   double distance4 = p.distanceSquaredTo(Point(this->getX2(), this->getY2()));
   return std::min( std::min(distance1, distance2), std::min(distance3, distance4) );
}