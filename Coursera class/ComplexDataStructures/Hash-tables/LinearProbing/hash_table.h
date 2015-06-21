#pragma once
#include <vector>

template <class T, class U>
class HashTable
{
   struct value
   {
      value() : exist (false) {}
      value(const value& rhs) : exist(rhs.exist), key(rhs.key), val(rhs.val) {}
      value(const T& _key, const U& _val) : exist (true), key(_key), val(_val) {}
      value& operator =(const value& rhs) 
      {
         exist = rhs.exist;
         key = rhs.key;
         val = rhs.val;
         return *this;
      }
      bool exist;
      T key;
      U val;
   };
public:
   HashTable()
   {
      vect.resize(T::maxHashCode() + 1);
   }

   ~HashTable() 
   {
   }
   
   void insert(const T& key, const U& val)
   {
      unsigned int index = key.hashCode();
      unsigned int i = index;
      while (vect[i].exist)
      {
         if (vect[i].key == key)
            throw std::runtime_error("Такой элемент уже есть");
         i++;
         if (i == vect.size())
            i = 0;
         if (i == index)
            throw std::runtime_error("Нет свободных ячеек");
      }
      vect[i] = value(key, val);
   }
   
   bool find(const T& key)
   {
      unsigned int index = key.hashCode();
      unsigned int i = index;
      while (vect[i].exist)
      {
         if (vect[i].key == key)
            return true;
         i++;
         if (i == vect.size())
            i = 0;
         if (i == index)
            return false;
      }
      return false;
   }
   
   U getValue(const T& key)
   {
      unsigned int index = key.hashCode();
      unsigned int i = index;
      while (vect[i].exist)
      {
         if (vect[i].key == key)
            return vect[i].val;
         i++;
         if (i == vect.size())
            i = 0;
         if (i == index)
            break;
      }
      return U();
   }

private:
   std::vector<value> vect;
};