#pragma once
#include "Point.h"
#include <vector>

template <class T, class U>
class HashTable
{
public:
   HashTable()
   {
   }

   ~HashTable() 
   {
   }
   
   void insert(const T& key, const U& val)
   {
      unsigned int index = key.hashCode();
      if (vect.size() <= index)
         vect.resize(index + 1);
      vect[index] = val;
   }

   bool find(const T& key)
   {
      unsigned int index = key.hashCode();
      if (vect.size() <= index)
         return false;
      U val;
      return vect[index] != val;
   }

   U getValue(const T& key)
   {
      unsigned int index = key.hashCode();
      if (vect.size() <= index)
         return U();
      return vect[index];
   }

private:
   std::vector<U> vect;
};