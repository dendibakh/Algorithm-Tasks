#include "tree.h"
#include "RunAllTests.h"

void run()
{
	Tree t;

	t.insert(Complex(3, 3));	
	t.insert(Complex(2, 10));
	t.insert(Complex(1, 0));
	t.insert(Complex(0, 0));
	t.insert(Complex(10, 10));
	t.insert(Complex(1, 1));
	t.insert(Complex(1, 10));
	t.insert(Complex(2, 2));
	t.insert(Complex(3, 4));
	t.insert(Complex(7, 10));
	t.print();
	std::cout << std::endl;
	for(Tree::iterator it=t.begin(), end=t.end(); it!=end; it++)
		std::cout << (*it).toString() << std::endl;
	Tree::iterator it=t.begin();
	std::cout << *it;
	it++;
	std::cout << *it;
	//t.printLeftTraversal();
}
int main()
{
	RunAllTests();
	//run();
	system("PAUSE");
	return 0;
}