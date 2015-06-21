#include "Tree.h"
#include <iostream>

int main()
{
   Tree<int> tree;
   tree.insert(7);
   tree.insert(5);
   tree.insert(10);
   tree.insert(3);
   tree.insert(6);
   tree.insert(9);
   tree.insert(11);
   tree.insert(2);
   tree.insert(8);
   tree.insert(13);
   tree.insert(15);
   tree.printLeftTraversal();
   bool f1 = tree.find(15);
   bool f2 = tree.find(16);
   //std::cout << "Height of the tree is: " << tree.height() << std::endl;
   tree.remove(15);
   std::cout << "remove 15" << std::endl;
   tree.printLeftTraversal();
   tree.remove(3);
   std::cout << "remove 3" << std::endl;
   tree.printLeftTraversal();
   tree.remove(7);
   std::cout << "remove 7" << std::endl;
   tree.printLeftTraversal();
}