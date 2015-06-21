#pragma once
#include "Point.h"
#include <vector>

template <class T, class U>
class HashTable
{
public:
   HashTable(int N) : size(N) , vect(N) 
   {
   }

   ~HashTable() 
   {
   }
   
   void insert(const T& key, const U& val)
   {
      vect[key.hashCode()] = val;
   }

   bool find(const T& key)
   {
      U val;
      return vect[key.hashCode()] != val;
   }

   U getValue(const T& key)
   {
      return vect[key.hashCode()];
   }

private:
   std::vector<U> vect;
   const int size;
};