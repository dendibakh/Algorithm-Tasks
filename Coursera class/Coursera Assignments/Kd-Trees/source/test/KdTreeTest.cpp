#include "TestHarness.h"
#include "KdTree.h"

TEST (KdTree, construct)
{
   KdTree::PointSET p;
}

TEST (KdTree, isEmpty)
{
   KdTree::PointSET p;
   CHECK(p.isEmpty());
}

TEST (KdTree, size)
{
   KdTree::PointSET p;
   CHECK_EQUAL(0, p.size());
}

TEST (KdTree, insert)
{
   KdTree::PointSET pSet;
   pSet.insert(Point(7, 2));
   CHECK(!pSet.isEmpty());
   CHECK_EQUAL(1, pSet.size());
   pSet.insert(Point(5, 4));
   pSet.insert(Point(2, 3));
   pSet.insert(Point(4, 7));
   pSet.insert(Point(9, 6));
   pSet.insert(Point(5, 6));
   CHECK(!pSet.isEmpty());
   CHECK_EQUAL(6, pSet.size());
   //pSet.printLeftTraversal();
}

TEST (KdTree, contains)
{
   KdTree::PointSET pSet;
   pSet.insert(Point(7, 2));
   pSet.insert(Point(5, 4));
   pSet.insert(Point(2, 3));
   CHECK(!pSet.isEmpty());
   CHECK_EQUAL(3, pSet.size());
   CHECK(pSet.contains(Point(2, 3)));
   CHECK(pSet.contains(Point(7, 2)));
   CHECK(!pSet.contains(Point(2, 4)));
   CHECK(!pSet.contains(Point(5, 3)));
}

TEST (KdTree, range_coursera_example1)
{
   KdTree::PointSET pSet;
   pSet.insert(Point(7, 2));
   pSet.insert(Point(5, 4));
   pSet.insert(Point(2, 3));
   pSet.insert(Point(4, 7));
   pSet.insert(Point(9, 6));
   RectHV rect(0, 0, 3, 4);
   Point arr[] = {Point(2, 3)};
   size_t sizeofArr = sizeof(arr) / sizeof(arr[0]);
   std::list<Point> etalon(arr, arr + sizeofArr);
   std::list<Point> expected = pSet.range(rect);
   CHECK(std::equal(etalon.begin(), etalon.end(), expected.begin()));
}

TEST (KdTree, range_coursera_example2)
{
   KdTree::PointSET pSet;
   pSet.insert(Point(7, 2));
   pSet.insert(Point(5, 4));
   pSet.insert(Point(2, 3));
   pSet.insert(Point(4, 7));
   pSet.insert(Point(9, 6));
   RectHV rect(0, 5, 10, 10);
   Point arr[] = {Point(4, 7), Point(9, 6)};
   size_t sizeofArr = sizeof(arr) / sizeof(arr[0]);
   std::list<Point> etalon(arr, arr + sizeofArr);
   std::list<Point> expected = pSet.range(rect);
   CHECK(std::equal(etalon.begin(), etalon.end(), expected.begin()));
}

TEST (KdTree, range_coursera_example3)
{
   KdTree::PointSET pSet;
   pSet.insert(Point(7, 2));
   pSet.insert(Point(5, 4));
   pSet.insert(Point(2, 3));
   pSet.insert(Point(4, 7));
   pSet.insert(Point(9, 6));
   RectHV rect(3, 0, 6, 3);
   std::list<Point> expected = pSet.range(rect);
   CHECK_EQUAL(0, expected.size());
}

TEST (KdTree, range1)
{
   KdTree::PointSET pSet;
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

TEST (KdTree, range2)
{
   KdTree::PointSET pSet;
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

TEST (KdTree, range3)
{
   KdTree::PointSET pSet;
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

TEST (KdTree, nearest1)
{
   KdTree::PointSET pSet;
   try
   {
      pSet.nearest(Point(0, 0));
      FAIL("There must be an exception");
   }
   catch (std::exception&)
   {}
}

TEST (KdTree, nearest2)
{
   KdTree::PointSET pSet;
   pSet.insert(Point(1, 2));
   CHECK(pSet.nearest(Point(0, 0)) == Point(1, 2));
   CHECK(pSet.nearest(Point(100, 100)) == Point(1, 2));
}

TEST (KdTree, nearest3)
{
   KdTree::PointSET pSet;
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