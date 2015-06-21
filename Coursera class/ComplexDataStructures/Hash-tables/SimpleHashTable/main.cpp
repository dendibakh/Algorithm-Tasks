#include "hash_table.h"
#include <iostream>

int main()
{
   HashTable htbl(100 * 100 + 100 + 1);
   Point p1(56, 81);
   Point p2(13, 49);
   Point p3(81, 56);
   Point p4(100, 100);
   Point p5(0, 0);
   htbl.insert(p1);
   htbl.insert(p2);
   htbl.insert(p3);
   htbl.insert(p4);
   bool find1 = htbl.find(p1);
   bool find3 = htbl.find(p3);
   bool find5 = htbl.find(p5);
   std::string str1 = htbl.getValue(p1);
   std::string str3 = htbl.getValue(p3);
   system("pause");
   return 0;
}