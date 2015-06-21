#include "tests.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "Brute-Force.h"
#include "KdTree.h"

static const int AmountOfPoints = 10000;
static const int FieldDimension = 1000;

// For AmountOfPoints = 10000 and FieldDimension = 1000, the results are:
//         Call Stack                                        CPU Time   CPU Time:Total
// checkTimeComplexity_range<class KdTree::PointSET>          0.020s     0.3%
// checkTimeComplexity_range<class BruteForce::PointSET>      0.010s     0.8%
// checkTimeComplexity_nearest<class KdTree::PointSET>            0s     0.3%
// checkTimeComplexity_nearest<class BruteForce::PointSET>        0s     0.7%

typedef std::vector<Point> PointVector;
typedef PointVector::const_iterator PointVectorIterator;

static Point getNewPoint()
{
   return Point(rand() % FieldDimension, rand() % FieldDimension);
}

static std::vector<Point> getSetOfPoints()
{
   srand (time(NULL));
   std::vector<Point> points;
   for (int i = 0; i < AmountOfPoints; i++)
   {
      Point newPoint = getNewPoint();
      PointVectorIterator iter = std::find (points.begin(), points.end(), newPoint);
      if (iter == points.end())
         points.push_back(newPoint);
      else
         i = i - 1;
   }
   return points;
}

template <class T>
std::list<Point> checkTimeComplexity_range(const std::vector<Point> & points, const RectHV& querryRect)
{
   T pSet;
   for (std::vector<Point>::const_iterator iter = points.begin(); iter != points.end(); ++iter)
   {
      pSet.insert(*iter);
   }
   return pSet.range(querryRect);
      
}

template <class T>
Point checkTimeComplexity_nearest(const std::vector<Point> & points, const Point& querryPoint)
{
   T pSet;
   for (std::vector<Point>::const_iterator iter = points.begin(); iter != points.end(); ++iter)
   {
      pSet.insert(*iter);
   }
   return pSet.nearest(querryPoint);
}

int main()
{
   //RunAllTest();
   std::vector<Point> pSet = getSetOfPoints();
   Point querryPoint = getNewPoint();
   RectHV querryRect(250, 250, 300, 300);
   //Point p1 = getNewPoint();
   //Point p2 = getNewPoint();
   //RectHV querryRect(p1.getX(), p1.getY(), p2.getX(), p2.getY());
   
   std::list<Point> KdTreeList = checkTimeComplexity_range<KdTree::PointSET>(pSet, querryRect);
   std::list<Point> BruteForceList = checkTimeComplexity_range<BruteForce::PointSET>(pSet, querryRect);
   Point KdTreePoint = checkTimeComplexity_nearest<KdTree::PointSET>(pSet, querryPoint);
   Point BruteForcePoint = checkTimeComplexity_nearest<BruteForce::PointSET>(pSet, querryPoint);

   //system("pause");
   return 0;
}