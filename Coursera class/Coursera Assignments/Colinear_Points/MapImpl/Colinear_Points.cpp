#include "Colinear_Points.h"
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <time.h>

// �������� �� ���� ॠ����樨:
// 1. �������. �६� N^4. ��ॡ�� ��� �祪. ��宦����� ������� ��� ��� ��⠫��� �祪. ��⥬ ����� �� �ᥬ �窠� � �饬 ��������� �������.
// 2. ����஢���. �६� N^3 * log(N). ��ॡ�� ��� �祪. ����� ��� ��������. ����஢�� ����祭��� ���祭��. ���� � �����஢����� ���ᨢ� �� ���� ��室.
// 3. �ᯮ���� std::multimap. �६� N^2 * log(D). �஡������� �� �ᥬ �窠�. ��� ������ �窨 ����塞 ������ ��� ��㣨� �祪. ����祭�� ���祭�� ᪫��뢠�� � multimap. 
//    ���� �� ������� ���祭�� ����, 㧭��� ������⢮ �㡫���⮢.

// ���������� ��⨩ ��ਠ��.

// ��襥 �६� �믮������ N * ( N + D^2 ), ��� D - ࠧ��୮���.
// ��ᯥਬ��⠫쭮 �६� ����稫��� N^2.45.

// �� ����॥ �㤥� ࠡ���� ���-⠡���. ��� ������ �㤥� ࠡ���� �� �६� N * ( N + C ), ��� C - ������� ����⠭�. ���쪮 ���� �ਤ㬠�� ��� ������� ��� ��� �����.

static const int AmountOfPoints = 1000;
static const int SequenceQuantity = 4;
static const int FieldDimension = 100;

double slope(const Point& p1, const Point& p2)
{
   if (p1 == p2)
      return std::numeric_limits<double>::min();
   if (p1.getY() == p2.getY())
      return 0.;
   if (p1.getX() == p2.getX())
      return std::numeric_limits<double>::max();
   return (double)(p1.getY() - p2.getY()) / (double)(p1.getX() - p2.getX());
}

typedef std::vector<Point> PointVector;
typedef PointVector::const_iterator PointVectorIterator;

typedef std::multimap<double, Point> pointsMap;
typedef pointsMap::iterator pointsIter;

typedef std::multimap< double, std::set < Point > > linesMap;
typedef linesMap::iterator linesIter;

typedef std::set< Point >::iterator setIter;

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

static void printPoints(const std::vector<Point> & points)
{
   int i = 0;
   for (std::vector<Point>::const_iterator iter = points.begin(); iter != points.end(); ++iter)
   {
      std::cout << "Point " << ++i << ": " << "(" << iter->getX() << ";" << iter->getY() << ")" << std::endl;
   }
   std::cout << std::endl;
}

// �६� �믮������ ������ � N^2
static linesMap findLines(const std::vector<Point> & points)
{
   linesMap lines;
   // ���� �� �ᥬ �窠�. �६� N.
   for (std::vector<Point>::const_iterator iter = points.begin(); iter != points.end(); ++iter)
   {
      Point p1 = *iter;
      std::multimap<double, Point> slopes;
      std::set<double> lineSlopes;
      // ��室�� �� ����� �� 4 � ����� �祪, ���ᥪ��騥 ��� p1. �६� N.
      for (std::vector<Point>::const_iterator iter2 = points.begin(); iter2 != points.end(); ++iter2)
      {
         Point curPoint = *iter2;
         double curSlope = slope(p1, curPoint);
         slopes.insert(std::make_pair(curSlope, curPoint));
         if (slopes.count(curSlope) >= SequenceQuantity - 1) // ��⮬� �� ᠬ� ��� p1 ⮦� �㦭� ���뢠��.
         {
            std::set<double>::const_iterator set_iter = lineSlopes.find(curSlope);
            if(set_iter == lineSlopes.end())
               lineSlopes.insert(curSlope);
         }
      }

      // �����뢠�� �������� ����� � ��騩 ���⥩���. ��襥 �६� D^2. (D - ࠧ��୮���).
      for (std::set<double>::const_iterator set_it = lineSlopes.begin(); set_it != lineSlopes.end(); ++set_it)
      {
         std::set< Point > line;
         // ��⠢�� ᠬ�� �窨
         line.insert(p1);
         // ��⠢�� ��� ���������� �� �祪
         std::pair<pointsIter, pointsIter> ret = slopes.equal_range(*set_it);
         for (pointsIter it = ret.first; it != ret.second; ++it)
            line.insert(it->second);
         // �஢�ઠ, �� ⠪�� ����� �� ���
         bool found = false;
         std::pair<linesIter, linesIter> linesWithSuchSlope = lines.equal_range(*set_it);
         for (linesIter lineIt = linesWithSuchSlope.first; lineIt != linesWithSuchSlope.second; ++lineIt)
         {
            if (std::equal(lineIt->second.begin(), lineIt->second.end(), line.begin()))
            {
               found = true;
               break;
            }
         }
         // ������� १���� � ��騩 ���⥩���
         if (!found)
            lines.insert(std::make_pair(*set_it, line));
      }
   }
   return lines;
}

static void printLines(linesMap & lines)
{
   std::cout << "There are " << lines.size() << " lines of " << SequenceQuantity << " points:" << std::endl;
   int i = 0;
   for (linesIter lineIt = lines.begin(); lineIt != lines.end(); ++lineIt)
   {
      std::cout << std::endl << "Line " << ++i << ":" << std::endl;
      for (setIter pIter = lineIt->second.begin(); pIter != lineIt->second.end(); ++pIter)
      {
         std::cout << "Point " << ": " << "(" << pIter->getX() << ";" << pIter->getY() << ")" << std::endl;
      }
   }
}

int main()
{
   std::vector<Point> points = getSetOfPoints();
   printPoints(points);
   linesMap lines = findLines(points);
   printLines(lines);
   //system("pause");
}