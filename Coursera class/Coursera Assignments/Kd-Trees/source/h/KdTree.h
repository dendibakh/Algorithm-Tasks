#pragma once

#include "RecHV.h"
#include <map>
#include <list>

namespace KdTree
{
   class PointSET
   {
         struct node
         {
            Point value;
            node* left;
            node* right;
         };

         enum LEVEL_COORDINATE
         {
            X_COORD = 0,
            Y_COORD = 1
         };

         void destroy(node *&n);
         size_t size(node *n) const;
         void insert(node *&n, const Point& p, LEVEL_COORDINATE level);
         LEVEL_COORDINATE switchLevel(LEVEL_COORDINATE curLevel) const;
         bool lessByLevel(const Point& p1, const Point& p2, LEVEL_COORDINATE level) const;
         int height(node *n, int level) const;
         void printLeftTraversal(node *n, std::multimap<int, Point>& storage, int level) const;
         bool contains(node *n, const Point& p, LEVEL_COORDINATE level) const;
         void range(node *n, const RectHV& rect, std::list<Point>& retList) const;
         void range(node *n, const RectHV& rect, std::list<Point>& retList, LEVEL_COORDINATE level, const RectHV& considerRect) const;
         RectHV getLeftRect(const Point& p, LEVEL_COORDINATE level, const RectHV& considerRect) const;
         RectHV getRightRect(const Point& p, LEVEL_COORDINATE level, const RectHV& considerRect) const;
         void nearest(node *n, const Point& querryPoint, Point& bestPoint, LEVEL_COORDINATE level, const RectHV& considerRect) const;
         bool querryPointIsOnTheLeft(const Point& querryPoint, const Point& curPoint, LEVEL_COORDINATE level) const;

      public:
         PointSET();
         ~PointSET();
         bool isEmpty() const;
         size_t size() const;
         void insert(const Point& p);                      // add the point p to the set (if it is not already in the set)
         int height() const;
         void printLeftTraversal() const;
         bool contains(const Point& p) const;              // does the set contain the point p?
         std::list<Point> range(const RectHV& rect) const; // all points in the set that are inside the rectangle
         Point nearest(const Point& p) const;              // a nearest neighbor in the set to p
      private:
         node* root;
   };
}