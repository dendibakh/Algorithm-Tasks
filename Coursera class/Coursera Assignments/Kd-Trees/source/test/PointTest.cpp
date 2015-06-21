#include "TestHarness.h"
#include "Point.h"
#include <cmath>

TEST (Point, construct)
{
   Point p(1, 5);
   CHECK_EQUAL(p.getX(), 1);
   CHECK_EQUAL(p.getY(), 5);
}

TEST (Point, construct2)
{
   Point p(-1, -5);
   CHECK_EQUAL(p.getX(), -1);
   CHECK_EQUAL(p.getY(), -5);
}

TEST (Point, construct3)
{
   Point p(0, 0);
   CHECK_EQUAL(p.getX(), 0);
   CHECK_EQUAL(p.getY(), 0);
}

TEST (Point, construct4)
{
   Point p(1, 1);
   Point p1(p);
   CHECK_EQUAL(p1.getX(), 1);
   CHECK_EQUAL(p1.getY(), 1);
}

TEST (Point, operatorAssign1)
{
   Point p(1, 1);
   Point p1(2, 2);
   p1 = p;
   CHECK_EQUAL(p1.getX(), 1);
   CHECK_EQUAL(p1.getY(), 1);
}

TEST (Point, operatorAssign2)
{
   Point p1(1, 1);
   Point p2(2, 2);
   Point p3(3, 3);
   p1 = p2 = p3;
   CHECK_EQUAL(p1.getX(), 3);
   CHECK_EQUAL(p1.getY(), 3);
   CHECK_EQUAL(p2.getX(), 3);
   CHECK_EQUAL(p2.getY(), 3);
   CHECK_EQUAL(p3.getX(), 3);
   CHECK_EQUAL(p3.getY(), 3);
}

TEST (Point, operatorCompare1)
{
   Point p(1, 1);
   Point p1(2, 2);
   CHECK(!(p1==p));
}

TEST (Point, operatorCompare2)
{
   Point p(2, 2);
   Point p1(2, 2);
   CHECK(p1==p);
}

TEST (Point, operatorCompare3)
{
   Point p(2, 1);
   Point p1(2, 2);
   CHECK(!(p1==p));
}

TEST (Point, operatorLess1)
{
   Point p(0, 0);
   Point p1(1, 1);
   CHECK(p<p1);
}

TEST (Point, operatorLess2)
{
   Point p(1, 1);
   Point p1(1, 1);
   CHECK(!(p<p1));
}

TEST (Point, operatorLess3)
{
   Point p(1, 1);
   Point p1(0, 2);
   CHECK(p<p1);
}

TEST (Point, operatorLess4)
{
   Point p(1, 1);
   Point p1(1, 2);
   CHECK(p<p1);
}

TEST (Point, operatorLess5)
{
   Point p(1, 1);
   Point p1(2, 2);
   CHECK(p<p1);
}

TEST (Point, operatorLess6)
{
   Point p(1, 1);
   Point p1(2, 1);
   CHECK(p<p1);
}

TEST (Point, operatorLess7)
{
   Point p(1, 1);
   Point p1(2, 0);
   CHECK(!(p<p1));
}

TEST (Point, toString1)
{
   Point p(1, 1);
   CHECK_EQUAL(p.toString(), "Point (1;1)");
}

TEST (Point, toString2)
{
   Point p(0, 10);
   CHECK_EQUAL(p.toString(), "Point (0;10)");
}

TEST (Point, distanceTo1)
{
   Point p1(0, 0);
   Point p2(0, 0);
   CHECK_EQUAL(0.0, p1.distanceTo(p2));
}

TEST (Point, distanceTo2)
{
   Point p1(0, 10);
   Point p2(10, 10);
   CHECK_EQUAL(10.0, p1.distanceTo(p2));
}

TEST (Point, distanceTo3)
{
   Point p1(-10, -10);
   Point p2(10, 10);
   CHECK_EQUAL(sqrt(800.0), p1.distanceTo(p2));
}

TEST (Point, distanceTo4)
{
   Point p1(3, 3);
   Point p2(6, 7);
   CHECK_EQUAL(5.0, p1.distanceTo(p2));
}

TEST (Point, distanceTo5)
{
   Point p1(1, 1);
   Point p2(2, 2);
   CHECK_EQUAL(sqrt(2.0), p1.distanceTo(p2));
}

TEST (Point, distanceSquaredTo1)
{
   Point p1(0, 0);
   Point p2(0, 0);
   CHECK_EQUAL(0.0, p1.distanceSquaredTo(p2));
}

TEST (Point, distanceSquaredTo2)
{
   Point p1(0, 10);
   Point p2(10, 10);
   CHECK_EQUAL(100.0, p1.distanceSquaredTo(p2));
}

TEST (Point, distanceSquaredTo3)
{
   Point p1(-10, -10);
   Point p2(10, 10);
   CHECK_EQUAL(800.0, p1.distanceSquaredTo(p2));
}

TEST (Point, distanceSquaredTo4)
{
   Point p1(3, 3);
   Point p2(6, 7);
   CHECK_EQUAL(25.0, p1.distanceSquaredTo(p2));
}

TEST (Point, distanceSquaredTo5)
{
   Point p1(1, 1);
   Point p2(2, 2);
   CHECK_EQUAL(2.0, p1.distanceSquaredTo(p2));
}