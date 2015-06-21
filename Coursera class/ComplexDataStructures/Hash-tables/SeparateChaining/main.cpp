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
   Point p2(13, 49);
   Point p3(81, 56);
   Point p4(100, 100);
   Point p5(0, 0);
   insertOnePoint(htbl, p1);
   insertOnePoint(htbl, p2);
   insertOnePoint(htbl, p3);
   insertOnePoint(htbl, p4);
   bool find1 = htbl.find(p1);
   bool find3 = htbl.find(p3);
   bool find5 = htbl.find(p5);
   std::string str1 = htbl.getValue(p1);
   std::string str3 = htbl.getValue(p3);
   std::string str5 = htbl.getValue(p5);
   system("pause");
   return 0;
}