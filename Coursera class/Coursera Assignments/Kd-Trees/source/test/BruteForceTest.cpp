#include "TestHarness.h"
#include "Brute-Force.h"
#include <algorithm>

TEST (BruteForce, range1)
{
   BruteForce::PointSET pSet;
   pSet.insert(Point(1, 2));
   pSet.insert(Point(2, 5));
   pSet.insert(Point(4, 8));
   pSet.insert(Point(5, 2));
   pSet.insert(Point(7, 3));
   pSet.insert(Point(9, 6));
   RectHV rect(3, 4, 7, 7);
   std::list<Point> expected = pSet.range(rect);
   CHECK_EQUAL(0, expected.size());
}

TEST (BruteForce, range2)
{
   BruteForce::PointSET pSet;
   pSet.insert(Point(1, 2));
   pSet.insert(Point(2, 5));
   pSet.insert(Point(4, 5));
   pSet.insert(Point(4, 8));
   pSet.insert(Point(5, 2));
   pSet.insert(Point(6, 6));
   pSet.insert(Point(7, 3));
   pSet.insert(Point(9, 6));
   RectHV rect(3, 4, 7, 7);
   Point arr[] = {Point(4, 5), Point(6, 6)};
   size_t sizeofArr = sizeof(arr) / sizeof(arr[0]);
   std::list<Point> etalon(arr, arr + sizeofArr);
   std::list<Point> expected = pSet.range(rect);
   CHECK(std::equal(etalon.begin(), etalon.end(), expected.begin()));
}

TEST (BruteForce, range3)
{
   BruteForce::PointSET pSet;
   pSet.insert(Point(1, 2));
   pSet.insert(Point(2, 5));
   pSet.insert(Point(3, 4));
   pSet.insert(Point(4, 8));
   pSet.insert(Point(5, 2));
   pSet.insert(Point(7, 7));
   pSet.insert(Point(7, 3));
   pSet.insert(Point(9, 6));
   RectHV rect(3, 4, 7, 7);
   Point arr[] = {Point(3, 4), Point(7, 7)};
   size_t sizeofArr = sizeof(arr) / sizeof(arr[0]);
   std::list<Point> etalon(arr, arr + sizeofArr);
   std::list<Point> expected = pSet.range(rect);
   CHECK(std::equal(etalon.begin(), etalon.end(), expected.begin()));
}

TEST (BruteForce, nearest1)
{
   BruteForce::PointSET pSet;
   try
   {
      pSet.nearest(Point(0, 0));
      FAIL("There must be an exception");
   }
   catch (std::exception&)
   {}
}

TEST (BruteForce, nearest2)
{
   BruteForce::PointSET pSet;
   pSet.insert(Point(1, 2));
   CHECK(pSet.nearest(Point(0, 0)) == Point(1, 2));
   CHECK(pSet.nearest(Point(100, 100)) == Point(1, 2));
}

TEST (BruteForce, nearest3)
{
   BruteForce::PointSET pSet;
   pSet.insert(Point(1, 2));
   pSet.insert(Point(2, 5));
   pSet.insert(Point(4, 5));
   pSet.insert(Point(4, 8));
   pSet.insert(Point(5, 2));
   pSet.insert(Point(6, 6));
   pSet.insert(Point(7, 3));
   pSet.insert(Point(9, 6));
   CHECK(pSet.nearest(Point(0, 0)) == Point(1, 2));
   CHECK(pSet.nearest(Point(100, 100)) == Point(9, 6));
   CHECK(pSet.nearest(Point(4, 100)) == Point(4, 8));
   CHECK(pSet.nearest(Point(4, 0)) == Point(5, 2));
   CHECK(pSet.nearest(Point(0, 5)) == Point(2, 5));
   CHECK(pSet.nearest(Point(0, 6)) == Point(2, 5));
   CHECK(pSet.nearest(Point(0, 8)) == Point(2, 5));
   CHECK(pSet.nearest(Point(0, 9)) == Point(4, 8));
   CHECK(pSet.nearest(Point(3, 5)) == Point(2, 5));
   CHECK(pSet.nearest(Point(6, 2)) == Point(5, 2));
   CHECK(pSet.nearest(Point(6, 4)) == Point(7, 3));
   CHECK(pSet.nearest(Point(5, 4)) == Point(4, 5));
}