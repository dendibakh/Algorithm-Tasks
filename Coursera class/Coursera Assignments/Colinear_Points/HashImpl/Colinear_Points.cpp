#include "Colinear_Points.h"
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <time.h>
#include <unordered_map>

// Возможны три вида реализации:
// 1. Брутфорс. Время N^4. Перебор всех точек. Нахождение наклона для всех остальных точек. Затем бежим по всем точкам и ищем одинаковые наклоны.
// 2. Сортировкой. Время N^3 * log(N). Перебор всех точек. Расчет всех наклонов. Сортировка полученных значений. Поиск в отсортированном массиве за один проход.
// 3. Используя std::multimap. Время N^2 * log(D). Пробегаемся по всем точкам. Для каждой точки вычисляем наклон для других точек. Полученные значения складываем в multimap. 
//    Идем по каждому значению кдюча, узнаем количество дубликатов.

// Реализован третий вариант.

// Худшее время выполнения N * ( N + D^2 ), где D - размерность.
// Экспериментально время получилось N^2.45.

// Еще быстрее будет работать хэш-таблица. Тут алгоритм будет работать за время N * ( N + C ), где C - некоторая константа. Только надо придумать как вычислять хэш для линии.
// Вот результаты:
// Для AmountOfPoints = 1000  и FieldDimension = 100  : HashImpl - 23,2 сек (44%) ; MapImpl - 29,7 сек (56%)
// Для AmountOfPoints = 10000 и FieldDimension = 1000 : HashImpl - 2567,5 сек (44,4%) ; MapImpl - 3209,9 сек (55,6%)

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
   // Линия имеет формулу y = kx + b
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

   // Время выполнения близко к N^2
   linesMap findLines(const std::vector<Point> & points)
   {
      linesMap lines;
      // Цикл по всем точкам. Время N.
      for (std::vector<Point>::const_iterator iter = points.begin(); iter != points.end(); ++iter)
      {
         Point p1 = *iter;
         std::multimap<double, Point> slopes;
         std::set<double> lineSlopes;
         // Находим все линии из 4 и более точек, пересекающие точку p1. Время N.
         for (std::vector<Point>::const_iterator iter2 = points.begin(); iter2 != points.end(); ++iter2)
         {
            Point curPoint = *iter2;
            double curSlope = slope(p1, curPoint);
            slopes.insert(std::make_pair(curSlope, curPoint));
            if (slopes.count(curSlope) >= SequenceQuantity - 1) // Потому что саму точку p1 тоже нужно учитывать.
            {
               std::set<double>::const_iterator set_iter = lineSlopes.find(curSlope);
               if(set_iter == lineSlopes.end())
                  lineSlopes.insert(curSlope);
            }
         }

         // Складываем найденные линии в общий контейнер. Худшее время D^2. (D - размерность).
         for (std::set<double>::const_iterator set_it = lineSlopes.begin(); set_it != lineSlopes.end(); ++set_it)
         {
            std::set< Point > line;
            // Вставка самой точки
            line.insert(p1);
            // Вставка всех колинеарных ей точек
            std::pair<pointsIter, pointsIter> ret = slopes.equal_range(*set_it);
            for (pointsIter it = ret.first; it != ret.second; ++it)
               line.insert(it->second);
            // Проверка, что такой линии еще нет
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
            // Положим результат в общий контейнер
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

   // Время выполнения близко к N^2
   linesMap findLines(const std::vector<Point> & points)
   {
      linesMap lines;
      // Цикл по всем точкам. Время N.
      for (std::vector<Point>::const_iterator iter = points.begin(); iter != points.end(); ++iter)
      {
         Point p1 = *iter;
         std::multimap<double, Point> slopes;
         std::set<double> lineSlopes;
         // Находим все линии из 4 и более точек, пересекающие точку p1. Время N.
         for (std::vector<Point>::const_iterator iter2 = points.begin(); iter2 != points.end(); ++iter2)
         {
            Point curPoint = *iter2;
            double curSlope = slope(p1, curPoint);
            slopes.insert(std::make_pair(curSlope, curPoint));
            if (slopes.count(curSlope) >= SequenceQuantity - 1) // Потому что саму точку p1 тоже нужно учитывать.
            {
               std::set<double>::const_iterator set_iter = lineSlopes.find(curSlope);
               if(set_iter == lineSlopes.end())
                  lineSlopes.insert(curSlope);
            }
         }

         // Складываем найденные линии в общий контейнер. Худшее время D^2. (D - размерность).
         for (std::set<double>::const_iterator set_it = lineSlopes.begin(); set_it != lineSlopes.end(); ++set_it)
         {
            std::set< Point > line;
            // Вставка самой точки
            line.insert(p1);
            // Вставка всех колинеарных ей точек
            std::pair<pointsIter, pointsIter> ret = slopes.equal_range(*set_it);
            for (pointsIter it = ret.first; it != ret.second; ++it)
               line.insert(it->second);
            // Проверка, что такой линии еще нет
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
            // Положим результат в общий контейнер
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