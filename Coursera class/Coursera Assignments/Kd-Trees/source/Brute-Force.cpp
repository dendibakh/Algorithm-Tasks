#include "Brute-Force.h"
#include <limits>

namespace BruteForce
{
   PointSET::PointSET() 
   {

   }

   bool PointSET::isEmpty() const 
   {
      return storage.size() == 0;
   }
    
   size_t PointSET::size() const 
   {
      return storage.size();
   }

   void PointSET::insert(const Point& p) 
   {
      storage.insert(p);
   }

   bool PointSET::contains(const Point& p) const 
   {
      std::set<Point>::const_iterator i = storage.find(p);
      return i != storage.end();
   }

   std::list<Point> PointSET::range(const RectHV& rect) const
   {
      std::list<Point> retList;
      for (std::set<Point>::const_iterator i = storage.begin(); i != storage.end(); ++i)
      {
         if (rect.contains(*i))
            retList.push_back(*i);
      }
      return retList;
   }

   Point PointSET::nearest(const Point& p) const
   {
      if (isEmpty())
         throw std::runtime_error("Попытка поиска в пустом наборе");
      Point retPoint(0, 0);
      double distance = std::numeric_limits<double>::max();
      for (std::set<Point>::const_iterator i = storage.begin(); i != storage.end(); ++i)
      {
         double newdistance = p.distanceTo(*i);
         if (newdistance < distance)
         {
            distance = newdistance;
            retPoint = *i;
         }
      }
      return retPoint;
   }
}