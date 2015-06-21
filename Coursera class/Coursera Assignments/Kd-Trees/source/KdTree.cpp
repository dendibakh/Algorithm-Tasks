#include "KdTree.h"
#include <iostream>
#include <limits>

namespace KdTree
{
   PointSET::PointSET()
   {
      root = 0;
   }

   PointSET::~PointSET()
   {
      destroy(root);
   }

   void PointSET::destroy(node *&n)
   {
      if (n)
      {
         destroy(n->left);
         destroy(n->right);
         delete n;
      }
   }

   bool PointSET::isEmpty() const
   {
      return root == 0;
   }

   size_t PointSET::size() const
   {
      return size(root);
   }

   size_t PointSET::size(node *n) const
   {
      if (n)
      {
         return 1 + size(n->left) + size(n->right);
      }
      return 0;
   }

   void PointSET::insert(const Point& p)
   {
      insert(root, p, X_COORD);
   }

   void PointSET::insert(node *&n, const Point& p, LEVEL_COORDINATE level)
   {
      if (n)
      {
         if (p == n->value)
            throw std::runtime_error("Такой элемент уже есть");
         else if (lessByLevel(p, n->value, level))
            insert(n->left, p, switchLevel(level));
         else
            insert(n->right, p, switchLevel(level));
      }
      else
      {
         n = new node;
         n->value = p;
         n->left = 0;
         n->right = 0;
      }
   }

   bool PointSET::lessByLevel(const Point& p1, const Point& p2, LEVEL_COORDINATE level) const
   {
      if (X_COORD == level)
      {
         return p1.getX() < p2.getX();
      }
      return p1.getY() < p2.getY();
   }
   
   PointSET::LEVEL_COORDINATE PointSET::switchLevel(LEVEL_COORDINATE curLevel) const
   {
      if (X_COORD == curLevel)
         return Y_COORD;
      return X_COORD;
   }

   void PointSET::printLeftTraversal() const
   {
      int level = 0;
      std::multimap<int, Point> storage;
      printLeftTraversal(root, storage, level++);
      for (int i = 0; i < height(); i++)
      {
         std::pair<std::multimap<int, Point>::iterator, std::multimap<int, Point>::iterator> iters = storage.equal_range(i);
         for (std::multimap<int, Point>::iterator iter = iters.first; iter != iters.second; ++iter)
         {
            std::cout << iter->second.toString() << " ";
         }
         std::cout << std::endl;
      }
   }

   void PointSET::printLeftTraversal(node *n, std::multimap<int, Point>& storage, int level) const
   {
      if (n)
      {
         storage.insert(std::make_pair(level, n->value));
         level++;
         printLeftTraversal(n->left, storage, level);
         printLeftTraversal(n->right, storage, level);
      }
   }

   int PointSET::height(node *n, int level) const
   {
      if (n)
      {
         int leftHeight = height(n->left, level);
         int rightHeight = height(n->right, level);
         return level + std::max(leftHeight, rightHeight) + 1;
      }
      return 0;
   }
   
   int PointSET::height() const
   {
      return height(root, 0);
   }

   bool PointSET::contains(const Point& p) const
   {
      return contains(root, p, X_COORD);
   }

   bool PointSET::contains(node *n, const Point& p, LEVEL_COORDINATE level) const
   {
      if (n)
      {
         if (p == n->value)
            return true;
         else if (lessByLevel(p, n->value, level))
            return contains(n->left, p, switchLevel(level));
         else
            return contains(n->right, p, switchLevel(level));
      }
      return false;
   }

   std::list<Point> PointSET::range(const RectHV& rect) const
   {
      RectHV considerRect(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
      std::list<Point> retList;
      range(root, rect, retList, X_COORD, considerRect);
      return retList;
   }

   // Range search. To find all points contained in a given query rectangle, start at the root and recursively search for points in both subtrees using the following pruning rule: 
   // if the query rectangle does not intersect the rectangle corresponding to a node, there is no need to explore that node (or its subtrees). 
   // A subtree is searched only if it might contain a point contained in the query rectangle.
   void PointSET::range(node *n, const RectHV& rect, std::list<Point>& retList, LEVEL_COORDINATE level, const RectHV& considerRect) const
   {
      if (n)
      {
         if (rect.contains(n->value))
            retList.push_back(n->value);
         if (n->left)
         {
            RectHV leftRect = getLeftRect(n->value, level, considerRect);
            if (rect.intersects(leftRect))
               range(n->left, rect, retList, switchLevel(level), leftRect);
         }
         if (n->right)
         {
            RectHV rightRect = getRightRect(n->value, level, considerRect);
            if (rect.intersects(rightRect))
               range(n->right, rect, retList, switchLevel(level), rightRect);
         }
      }
   }

   RectHV PointSET::getLeftRect(const Point& p, LEVEL_COORDINATE level, const RectHV& considerRect) const
   {
      if (X_COORD == level)
         return RectHV(considerRect.getX1(), considerRect.getY1(), p.getX(), considerRect.getY2());
      return RectHV(considerRect.getX1(), considerRect.getY1(), considerRect.getX2(), p.getY());
   }

   RectHV PointSET::getRightRect(const Point& p, LEVEL_COORDINATE level, const RectHV& considerRect) const
   {
      if (X_COORD == level)
         return RectHV(p.getX(), considerRect.getY1(), considerRect.getX2(), considerRect.getY2());
      return RectHV(considerRect.getX1(), p.getY(), considerRect.getX2(), considerRect.getY2());
   }

   Point PointSET::nearest(const Point& p) const
   {
      if (isEmpty())
         throw std::runtime_error("Попытка поиска в пустом наборе");
      RectHV considerRect(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
      Point best = root->value;
      nearest(root, p, best, X_COORD, considerRect);
      return best;
   }

   // Nearest neighbor search. To find a closest point to a given query point, start at the root and recursively search in both subtrees using the following pruning rule: 
   // if the closest point discovered so far is closer than the distance between the query point and the rectangle corresponding to a node, 
   // there is no need to explore that node (or its subtrees). That is, a node is searched only if it might contain a point that is closer than the best one found so far. 
   // The effectiveness of the pruning rule depends on quickly finding a nearby point. To do this, organize your recursive method so 
   // that when there are two possible subtrees to go down, you always choose the subtree that is on the same side of the splitting line as the query point 
   // as the first subtree to explore-the closest point found while exploring the first subtree may enable pruning of the second subtree.
   void PointSET::nearest(node *n, const Point& querryPoint, Point& bestPoint, LEVEL_COORDINATE level, const RectHV& considerRect) const
   {
      if (n)
      {
         double closestDistance = querryPoint.distanceTo(bestPoint);
         double currentDistance = querryPoint.distanceTo(n->value);
         if (currentDistance < closestDistance)
         {
            closestDistance = currentDistance;
            bestPoint = n->value;
         }
         RectHV leftRect  = getLeftRect (n->value, level, considerRect);
         RectHV rightRect = getRightRect(n->value, level, considerRect);
         bool discoverLeft = n->left && (leftRect.distanceTo(querryPoint) < closestDistance);
         bool discoverRight = n->right && (rightRect.distanceTo(querryPoint) < closestDistance);
         if (discoverLeft && discoverRight)
         {
            if (querryPointIsOnTheLeft(querryPoint, n->value, level))
            {
               nearest(n->left, querryPoint, bestPoint, switchLevel(level), leftRect);
               nearest(n->right, querryPoint, bestPoint, switchLevel(level), rightRect);
            }
            else
            {
               nearest(n->right, querryPoint, bestPoint, switchLevel(level), rightRect);
               nearest(n->left, querryPoint, bestPoint, switchLevel(level), leftRect);
            }
         }
         else if (discoverLeft)
         {
            nearest(n->left, querryPoint, bestPoint, switchLevel(level), leftRect);
         }
         else if (discoverRight)
         {
            nearest(n->right, querryPoint, bestPoint, switchLevel(level), rightRect);
         }
      }
   }

   bool PointSET::querryPointIsOnTheLeft(const Point& querryPoint, const Point& curPoint, LEVEL_COORDINATE level) const
   {
      if (X_COORD == level)
         return querryPoint.getX() < curPoint.getX();
      return querryPoint.getY() < curPoint.getY();   
   }
}