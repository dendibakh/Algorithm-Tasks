#include "Colinear_Points.h"
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <time.h>
#include <unordered_map>

// �������� �� ���� ॠ����樨:
// 1. �������. �६� N^4. ��ॡ�� ��� �祪. ��宦����� ������� ��� ��� ��⠫��� �祪. ��⥬ ����� �� �ᥬ �窠� � �饬 ��������� �������.
// 2. ����஢���. �६� N^3 * log(N). ��ॡ�� ��� �祪. ����� ��� ��������. ����஢�� ����祭��� ���祭��. ���� � �����஢����� ���ᨢ� �� ���� ��室.
// 3. �ᯮ���� std::multimap. �६� N^2 * log(D). �஡������� �� �ᥬ �窠�. ��� ������ �窨 ����塞 ������ ��� ��㣨� �祪. ����祭�� ���祭�� ᪫��뢠�� � multimap. 
//    ���� �� ������� ���祭�� ����, 㧭��� ������⢮ �㡫���⮢.

// ���������� ��⨩ ��ਠ��.

// ��襥 �६� �믮������ N * ( N + D^2 ), ��� D - ࠧ��୮���.
// ��ᯥਬ��⠫쭮 �६� ����稫��� N^2.45.

// �� ����॥ �㤥� ࠡ���� ���-⠡���. ��� ������ �㤥� ࠡ���� �� �६� N * ( N + C ), ��� C - ������� ����⠭�. ���쪮 ���� �ਤ㬠�� ��� ������� ��� ��� �����.
// ��� १�����:
// ��� AmountOfPoints = 1000  � FieldDimension = 100  : HashImpl - 23,2 ᥪ (44%) ; MapImpl - 29,7 ᥪ (56%)
// ��� AmountOfPoints = 10000 � FieldDimension = 1000 : HashImpl - 2567,5 ᥪ (44,4%) ; MapImpl - 3209,9 ᥪ (55,6%)

static const int AmountOfPoints = 10000;
static const int SequenceQuantity = 4;
static const int FieldDimension = 1000;

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

typedef std::set< Point >::iterator setIter;

Point getNewPoint()
{
   return Point(rand() % FieldDimension, rand() % FieldDimension);
}

std::vector<Point> getSetOfPoints()
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
                
void printPoints(const std::vector<Point> & points)
{
   int i = 0;
   for (std::vector<Point>::const_iterator iter = points.begin(); iter != points.end(); ++iter)
   {
      std::cout << "Point " << ++i << ": " << "(" << iter->getX() << ";" << iter->getY() << ")" << std::endl;
   }
   std::cout << std::endl;
}

namespace HashImpl
{
   // ����� ����� ���� y = kx + b
   struct funcFormula
   {
      int k;
      int b;
   };

   template<class T> class MyHashFunction;
    
   template<>
   class MyHashFunction<funcFormula> 
   {
   public:
       size_t operator()(const funcFormula &f) const
       {
           return (f.k + FieldDimension ) * FieldDimension + f.b + FieldDimension;
       }
   };

   funcFormula calcFormula(const std::pair<Point, Point>& points)
   {
      funcFormula f;
      if (points.second.getX() == points.first.getX())
         f.k = 0;
      else
         f.k = ( points.second.getY() - points.first.getY() ) / (points.second.getX() - points.first.getX());
      f.b = points.second.getY() - points.second.getX() * f.k;
      return f;
   }

   template<class T> class MyCompare;

   template <> 
   struct MyCompare<funcFormula> 
   {
     bool operator() (const funcFormula& f1, const funcFormula& f2) const 
     {
        return f1.k == f2.k && f1.b == f2.b;
     }
   };

   typedef std::unordered_map< funcFormula, std::set < Point >, MyHashFunction<funcFormula>, MyCompare<funcFormula> > linesMap;
   typedef linesMap::iterator linesIter;

   // �६� �믮������ ������ � N^2
   linesMap findLines(const std::vector<Point> & points)
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
            auto pointIt = line.begin();
            Point p1 = *pointIt;
            Point p2 = *(++pointIt);
            funcFormula f = calcFormula(std::make_pair(p1, p2));
            auto lineIt = lines.find(f);
            if (lineIt == lines.end())
               lines.insert(std::make_pair(f, line));
            /*bool found = false;
            std::pair<linesIter, linesIter> linesWithSuchSlope = lines.equal_range(*set_it);
            for (linesIter lineIt = linesWithSuchSlope.first; lineIt != linesWithSuchSlope.second; ++lineIt)
            {
               if (std::equal(lineIt->second.begin(), lineIt->second.end(), line.begin()))
               {
                  found = true;
                  break;
               }
            }*/
            // ������� १���� � ��騩 ���⥩���
            //if (!found)
            //   lines.insert(std::make_pair(*set_it, line));
         }
      }
      return lines;
   }

   void printLines(linesMap & lines)
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
}

namespace MapImpl
{
   typedef std::multimap< double, std::set < Point > > linesMap;
   typedef linesMap::iterator linesIter;

   // �६� �믮������ ������ � N^2
   linesMap findLines(const std::vector<Point> & points)
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

   void printLines(linesMap & lines)
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
}

int main()
{
   std::vector<Point> points = getSetOfPoints();
   //printPoints(points);
   {
      HashImpl::linesMap lines = HashImpl::findLines(points);
      //HashImpl::printLines(lines);
      //std::cout << "HashImpl : " << lines.size() << " lines" << std::endl;
   }
   {
      MapImpl::linesMap lines = MapImpl::findLines(points);
      //MapImpl::printLines(lines);
      //std::cout << "MapImpl : " << lines.size() << " lines" << std::endl;
   }
   //system("pause");
}