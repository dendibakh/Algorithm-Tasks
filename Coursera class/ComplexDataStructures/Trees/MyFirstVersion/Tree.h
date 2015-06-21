#pragma once

#include <map>
#include <iostream>
#include <algorithm>

template <class T>
class Tree
{
private:
   struct node
   {
      T value;
      node* left;
      node* right;
   };
   
   void insert(node *&n, T value)
   {
      if (n)
      {
         if (value == n->value)
            return;//throw std::exception();
         if (value > n->value)
            insert(n->right, value);
         if (value < n->value)
            insert(n->left, value);
      }
      else
      {
         n = new node;
         n->value = value;
         n->left = 0;
         n->right = 0;
      }
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

   void printLeftTraversal(node *&n, std::multimap<int, T>& storage, int level)
   {
      if (n)
      {
         storage.insert(std::make_pair(level, n->value));
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

   bool find(node *&n, T value)
   {
      if (n)
      {
         if (value == n->value)
            return true;
         if (value > n->value)
            return find(n->right, value);
         if (value < n->value)
            return find(n->left, value);
      }
      return false;
   }

   void remove(node *&n)
   {
      if ((!n->right) && (!n->left))
      {
         delete n;
         n = 0;
      }
      else if ((n->right) && (n->left))
      {
         if (n->right->left)
         {
            n->value = n->right->left->value;
            remove(n->right->left);
         }
         else
         {
            n->value = n->right->value;
            node* temp = n->right->right;
            delete n->right;
            n->right = temp;
         }
      }
      else
      {
         node* temp = 0;
         if (n->right)
            temp = n->right;
         else if (n->left)
            temp = n->left;
         delete n;
         n = temp;
      }
   }

   void remove(node *&n, T value)
   {
      if (n)
      {
         if (value > n->value)
            remove(n->right, value);
         if (value < n->value)
            remove(n->left, value);
         if (value == n->value)
            remove(n);
      }
   }

public:
   Tree()
   {
      root = 0;
   }

   ~Tree()
   {
      destroy(root);
   }

   void insert(T value)
   {
      insert(root, value);
   }

   void printLeftTraversal()
   {
      int level = 0;
      std::multimap<int, T> storage;
      printLeftTraversal(root, storage, level++);
      for (int i = 0; i < height(); i++)
      {
         std::pair<std::multimap<int, T>::iterator, std::multimap<int, T>::iterator> iters = storage.equal_range(i);
         for (std::multimap<int, T>::iterator iter = iters.first; iter != iters.second; ++iter)
         {
            std::cout << iter->second << " ";
         }
         std::cout << std::endl;
      }
   }

   int height()
   {
      return height(root, 0);
   }

   bool find(T value)
   {
      return find(root, value);
   }

   void remove(T value)
   {
      remove(root, value);
   }

private:
   node* root;
};