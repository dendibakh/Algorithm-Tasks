#pragma once

#include <map>
#include <list>
#include <iostream>
#include <algorithm>
#include "Operations.h"

struct NextExpr
{
   int value;
   int operation;
};

class ComputationalTree
{
private:
   struct node
   {
      NextExpr key;
      node* left;
      node* right;
   };

   void insert(const NextExpr& expr)
   {
      if (!prevInsert)
      {
         insert(prevInsert, expr);
         root = prevInsert;
         return;
      }

      if ((expr.operation == OPER_MULTI) || (expr.operation == OPER_DIV))
         insertLeft(prevInsert, expr);
      else if ((expr.operation == OPER_PLUS) || (expr.operation == OPER_MINUS))
         insertRight(prevInsert, expr);
   }
   
   void insertLeft(node *&n, const NextExpr& expr)
   {
      if (n->left)
         insertLeft(n->left, expr);
      else
         insert(n->left, expr);
   }

   void insertRight(node *&n, const NextExpr& expr)
   {
      insert(n->right, expr);
      prevInsert = n->right;
   }

   void insert(node *&n, const NextExpr& expr)
   {
      n = new node;
      n->key.value = expr.value;
      n->key.operation = expr.operation;
      n->left = 0;
      n->right = 0;
   }

   void destroy(node *&n)
   {
      if (n)
      {
         destroy(n->left);
         destroy(n->right);
         delete n;
      }
   }

   void printLeftTraversal(node *&n, std::multimap<int, NextExpr>& storage, int level)
   {
      if (n)
      {
         storage.insert(std::make_pair(level, n->key));
         level++;
         printLeftTraversal(n->left, storage, level);
         printLeftTraversal(n->right, storage, level);
      }
   }

   int height(node *&n, int level)
   {
      if (n)
      {
         int leftHeight = height(n->left, level);
         int rightHeight = height(n->right, level);
         return level + std::max(leftHeight, rightHeight) + 1;
      }
      return 0;
   }

   double result(node *&n)
   {
      double left = resultLeft(n);
      if (n->key.operation == OPER_MINUS)
         left = -left;
      if (n->right)
         return left + result(n->right);
      return left;
   }

   double resultLeft(node *&n)
   {
      if (n->left)
      {
         if (n->left->key.operation == OPER_MULTI)
            return n->key.value * resultLeft(n->left);
         else if (n->left->key.operation == OPER_DIV)
            return n->key.value / resultLeft(n->left);
      }
      return n->key.value;
   }

public:
   ComputationalTree(const std::list<NextExpr>& vect)
   {
      root = 0;
      prevInsert = 0;
      for (std::list<NextExpr>::const_iterator iter = vect.begin(); iter != vect.end(); ++iter)
      {
         insert(*iter);
      }
   }

   ~ComputationalTree()
   {
      destroy(root);
   }

   void printLeftTraversal()
   {
      int level = 0;
      std::multimap<int, NextExpr> storage;
      printLeftTraversal(root, storage, level++);
      for (int i = 0; i < height(); i++)
      {
         std::pair<std::multimap<int, NextExpr>::iterator, std::multimap<int, NextExpr>::iterator> iters = storage.equal_range(i);
         for (std::multimap<int, NextExpr>::iterator iter = iters.first; iter != iters.second; ++iter)
         {
            std::cout << iter->second.value << " ";
         }
         std::cout << std::endl;
      }
   }

   int height()
   {
      return height(root, 0);
   }

   double result()
   {
      return result(root);
   }

private:
   node* root;
   node* prevInsert;
};
