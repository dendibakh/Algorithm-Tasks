#pragma once
#include <vector>
#include <list>

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
      for (std::list<std::pair<T,U>>::iterator i = vect[index].begin(); i != vect[index].end(); ++i)
      {
         if (key == i->first)
            return;
      }
      vect[index].push_back(std::make_pair(key, val));
   }
   
   bool find(const T& key)
   {
      unsigned int index = key.hashCode();
      if (vect.size() <= index)
         return false;
      for (std::list<std::pair<T,U>>::iterator i = vect[index].begin(); i != vect[index].end(); ++i)
      {
         if (key == i->first)
            return true;
      }
      return false;
   }

   U getValue(const T& key)
   {
      unsigned int index = key.hashCode();
      if (vect.size() <= index)
         return U();
      for (std::list<std::pair<T,U>>::iterator i = vect[index].begin(); i != vect[index].end(); ++i)
      {
         if (key == i->first)
            return i->second;
      }
      return U();
   }

private:
   std::vector<std::list<std::pair<T,U>>> vect;
};