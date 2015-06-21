#include "TestHarness.h"
#include "RecHV.h"
#include <cmath>

TEST (RectHV, construct)
{
   RectHV rect(1, 5, 2, 6);
   CHECK_EQUAL(rect.getX1(), 1);
   CHECK_EQUAL(rect.getY1(), 5);
   CHECK_EQUAL(rect.getX2(), 2);
   CHECK_EQUAL(rect.getY2(), 6);
}

TEST (RectHV, construct2)
{
   RectHV rect(-1, -5, -2, -6);
   CHECK_EQUAL(rect.getX1(), -1);
   CHECK_EQUAL(rect.getY1(), -5);
   CHECK_EQUAL(rect.getX2(), -2);
   CHECK_EQUAL(rect.getY2(), -6);
}

TEST (RectHV, construct3)
{
   try
   {
      RectHV rect(0, 0, 0, 5);
      FAIL("There must be an exception");
   }
   catch (std::exception&)
   {
   }
}

TEST (RectHV, construct4)
{
   try
   {
      RectHV rect(0, 5, 2, 5);
      FAIL("There must be an exception");
   }
   catch (std::exception&)
   {
   }
}

TEST (RectHV, construct5)
{
   try
   {
      RectHV rect(0, 5, 0, 5);
      FAIL("There must be an exception");
   }
   catch (std::exception&)
   {
   }
}

TEST (RectHV, construct6)
{
   RectHV rect1(1, 1, 2, 2);
   RectHV rect2(rect1);
   CHECK_EQUAL(1, rect2.getX1());
   CHECK_EQUAL(1, rect2.getY1());
   CHECK_EQUAL(2, rect2.getX2());
   CHECK_EQUAL(2, rect2.getY2());
}

TEST (RectHV, operatorAssign1)
{
   RectHV rect1(1, 1, 2, 2);
   RectHV rect2(2, 2, 3, 3);
   rect1 = rect2;
   CHECK_EQUAL(2, rect1.getX1());
   CHECK_EQUAL(2, rect1.getY1());
   CHECK_EQUAL(3, rect1.getX2());
   CHECK_EQUAL(3, rect1.getY2());
}

TEST (RectHV, operatorAssign2)
{
   RectHV rect1(1, 1, 2, 2);
   RectHV rect2(2, 2, 3, 3);
   RectHV rect3(3, 3, 4, 4);
   rect1 = rect2 = rect3;
   CHECK_EQUAL(3, rect1.getX1());
   CHECK_EQUAL(3, rect1.getY1());
   CHECK_EQUAL(4, rect1.getX2());
   CHECK_EQUAL(4, rect1.getY2());
   CHECK_EQUAL(3, rect2.getX1());
   CHECK_EQUAL(3, rect2.getY1());
   CHECK_EQUAL(4, rect2.getX2());
   CHECK_EQUAL(4, rect2.getY2());
   CHECK_EQUAL(3, rect3.getX1());
   CHECK_EQUAL(3, rect3.getY1());
   CHECK_EQUAL(4, rect3.getX2());
   CHECK_EQUAL(4, rect3.getY2());
}

TEST (RectHV, operatorCompare1)
{
   RectHV rect1(1, 1, 2, 2);
   RectHV rect2(2, 2, 3, 3);
   CHECK(!(rect1==rect2));
}

TEST (RectHV, operatorCompare2)
{
   RectHV rect1(1, 1, 2, 2);
   RectHV rect2(1, 1, 3, 3);
   CHECK(!(rect1==rect2));
}

TEST (RectHV, operatorCompare3)
{
   RectHV rect1(1, 1, 2, 2);
   RectHV rect2(1, 1, 2, 2);
   CHECK(rect1==rect2);
}

TEST (RectHV, toString1)
{
   RectHV rect1(1, 1, 2, 2);
   CHECK_EQUAL(rect1.toString(), "Rectangle (1;1) - (2;2)");
}

TEST (RectHV, toString2)
{
   RectHV rect1(0, 0, 2, 2);
   CHECK_EQUAL(rect1.toString(), "Rectangle (0;0) - (2;2)");
}

TEST (RectHV, contains1)
{
   RectHV rect(0, 0, 2, 2);
   Point p(3, 3);
   CHECK(!rect.contains(p));
}                  

TEST (RectHV, contains2)
{
   RectHV rect(0, 0, 4, 4);
   Point p(3, 3);
   CHECK(rect.contains(p));
}                  

TEST (RectHV, contains3)
{
   RectHV rect(0, 0, 3, 3);
   Point p(3, 3);
   CHECK(rect.contains(p));
}                  

TEST (RectHV, contains4)
{
   RectHV rect(3, 3, 5, 5);
   Point p(3, 3);
   CHECK(rect.contains(p));
}

TEST (RectHV, contains5)
{
   RectHV rect(-1, -1, 5, 5);
   Point p(-2, -2);
   CHECK(!rect.contains(p));
}

TEST (RectHV, intersects1)
{
   RectHV rect1(0, 0, 2, 2);
   RectHV rect2(0, 0, 2, 2);
   CHECK(rect1.intersects(rect2));
   CHECK(rect2.intersects(rect1));
}

TEST (RectHV, intersects2)
{
   RectHV rect1(0, 0, 2, 2);
   RectHV rect2(3, 3, 2, 2);
   CHECK(rect1.intersects(rect2));
   CHECK(rect2.intersects(rect1));
}

TEST (RectHV, intersects3)
{
   RectHV rect1(0, 0, 1, 1);
   RectHV rect2(3, 3, 2, 2);
   CHECK(!rect1.intersects(rect2));
   CHECK(!rect2.intersects(rect1));
}

TEST (RectHV, intersects4)
{
   RectHV rect1(0, 0, 1, 1);
   RectHV rect2(1, 1, 2, 2);
   CHECK(rect1.intersects(rect2));
   CHECK(rect2.intersects(rect1));
}

TEST (RectHV, intersects5)
{
   RectHV rect1(0, 0, 1, 1);
   RectHV rect2(1, 0, 2, 1);
   CHECK(rect1.intersects(rect2));
   CHECK(rect2.intersects(rect1));
}

TEST (RectHV, intersects6)
{
   RectHV rect1(0, 0, 1, 1);
   RectHV rect2(0, 1, 1, 2);
   CHECK(rect1.intersects(rect2));
   CHECK(rect2.intersects(rect1));
}

TEST (RectHV, intersects7)
{
   RectHV rect1(0, 0, 1, 1);
   RectHV rect2(0, 0, 1, -1);
   CHECK(rect1.intersects(rect2));
   CHECK(rect2.intersects(rect1));
}

TEST (RectHV, intersects8)
{
   RectHV rect1(0, 0, 1, 1);
   RectHV rect2(0, 0, -1, -1);
   CHECK(rect1.intersects(rect2));
   CHECK(rect2.intersects(rect1));
}

TEST (RectHV, intersects9)
{
   RectHV rect1(0, 0, 1, 1);
   RectHV rect2(0, 0, -1, 1);
   CHECK(rect1.intersects(rect2));
   CHECK(rect2.intersects(rect1));
}

TEST (RectHV, intersects10)
{
   RectHV rect1(0, 0, 1, 1);
   RectHV rect2(0, 2, 1, 3);
   CHECK(!rect1.intersects(rect2));
   CHECK(!rect2.intersects(rect1));
}

TEST (RectHV, distanceTo1)
{
   RectHV rect(3, 4, 7, 7);
   Point p(3, 4);
   CHECK_EQUAL(0.0, rect.distanceTo(p));
}

TEST (RectHV, distanceTo2)
{
   RectHV rect(3, 4, 7, 7);
   Point p(5, 5);
   CHECK_EQUAL(0.0, rect.distanceTo(p));
}

TEST (RectHV, distanceTo3)
{
   RectHV rect(3, 4, 7, 7);
   Point p(0, 5);
   CHECK_EQUAL(3.0, rect.distanceTo(p));
}

TEST (RectHV, distanceTo4)
{
   RectHV rect(3, 4, 7, 7);
   Point p(5, 0);
   CHECK_EQUAL(4.0, rect.distanceTo(p));
}

TEST (RectHV, distanceTo5)
{
   RectHV rect(3, 4, 7, 7);
   Point p(9, 5);
   CHECK_EQUAL(2.0, rect.distanceTo(p));
}

TEST (RectHV, distanceTo6)
{
   RectHV rect(3, 4, 7, 7);
   Point p(5, 8);
   CHECK_EQUAL(1.0, rect.distanceTo(p));
}

TEST (RectHV, distanceTo7)
{
   RectHV rect(3, 4, 7, 7);
   Point p(0, 0);
   CHECK_EQUAL(5.0, rect.distanceTo(p));
}

TEST (RectHV, distanceTo8)
{
   RectHV rect(3, 4, 7, 7);
   Point p(1, 8);
   CHECK_EQUAL(sqrt(5.0), rect.distanceTo(p));
}

TEST (RectHV, distanceTo9)
{
   RectHV rect(3, 4, 7, 7);
   Point p(10, 10);
   CHECK_EQUAL(sqrt(18.0), rect.distanceTo(p));
}

TEST (RectHV, distanceTo10)
{
   RectHV rect(3, 4, 7, 7);
   Point p(8, 0);
   CHECK_EQUAL(sqrt(17.0), rect.distanceTo(p));
}

TEST (RectHV, distanceSquaredTo1)
{
   RectHV rect(3, 4, 7, 7);
   Point p(3, 4);
   CHECK_EQUAL(0.0, rect.distanceSquaredTo(p));
}

TEST (RectHV, distanceSquaredTo2)
{
   RectHV rect(3, 4, 7, 7);
   Point p(5, 5);
   CHECK_EQUAL(0.0, rect.distanceSquaredTo(p));
}

TEST (RectHV, distanceSquaredTo3)
{
   RectHV rect(3, 4, 7, 7);
   Point p(0, 5);
   CHECK_EQUAL(9.0, rect.distanceSquaredTo(p));
}

TEST (RectHV, distanceSquaredTo4)
{
   RectHV rect(3, 4, 7, 7);
   Point p(5, 0);
   CHECK_EQUAL(16.0, rect.distanceSquaredTo(p));
}

TEST (RectHV, distanceSquaredTo5)
{
   RectHV rect(3, 4, 7, 7);
   Point p(9, 5);
   CHECK_EQUAL(4.0, rect.distanceSquaredTo(p));
}

TEST (RectHV, distanceSquaredTo6)
{
   RectHV rect(3, 4, 7, 7);
   Point p(5, 8);
   CHECK_EQUAL(1.0, rect.distanceSquaredTo(p));
}

TEST (RectHV, distanceSquaredTo7)
{
   RectHV rect(3, 4, 7, 7);
   Point p(0, 0);
   CHECK_EQUAL(25.0, rect.distanceSquaredTo(p));
}

TEST (RectHV, distanceSquaredTo8)
{
   RectHV rect(3, 4, 7, 7);
   Point p(1, 8);
   CHECK_EQUAL(5.0, rect.distanceSquaredTo(p));
}

TEST (RectHV, distanceSquaredTo9)
{
   RectHV rect(3, 4, 7, 7);
   Point p(10, 10);
   CHECK_EQUAL(18.0, rect.distanceSquaredTo(p));
}

TEST (RectHV, distanceSquaredTo10)
{
   RectHV rect(3, 4, 7, 7);
   Point p(8, 0);
   CHECK_EQUAL(17.0, rect.distanceSquaredTo(p));
}