#pragma once
#include "Point.h"
#include <vector>
#include <string>
#include <sstream>

//template <class T, class U>
class HashTable
{
public:
   HashTable(int N) : size(N) , vect(N) 
   {
   }

   ~HashTable() 
   {
   }
   
   void insert(const Point& p)
   {
      std::stringstream stream;
      stream << "Point " << ": " << "(" << p.getX() << ";" << p.getY() << ")";
      vect[p.hashCode()] = stream.str();
   }

   bool find(const Point& p)
   {
      
      return vect[p.hashCode()] != "";
   }

   std::string getValue(const Point& p)
   {
      return vect[p.hashCode()];
   }

private:
   std::vector<std::string> vect;
   const int size;
};