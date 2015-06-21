#include "hash_table.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Point.h"

void insertOnePoint(HashTable<Point, std::string>& htbl, const Point& p)
{
   std::stringstream stream;
   stream << "Point " << ": " << "(" << p.getX() << ";" << p.getY() << ")";
   htbl.insert(p, stream.str());
}

int main()
{
   HashTable<Point, std::string> htbl;
   Point p1(56, 81);
   Point p2(56, 82);
   Point p3(82, 56);
   Point p4(81, 56);
   Point p5(100, 100);
   Point p6(0, 0);
   insertOnePoint(htbl, p1);
   insertOnePoint(htbl, p2);
   insertOnePoint(htbl, p3);
   insertOnePoint(htbl, p4);
   insertOnePoint(htbl, p5);
   bool find1 = htbl.find(p1);
   bool find2 = htbl.find(p2);
   bool find3 = htbl.find(p3);
   bool find6 = htbl.find(p6);
   std::string str1 = htbl.getValue(p1);
   std::string str3 = htbl.getValue(p3);
   std::string str4 = htbl.getValue(p4);
   std::string str2 = htbl.getValue(p2);
   std::string str6 = htbl.getValue(p6);
   system("pause");
   return 0;
}