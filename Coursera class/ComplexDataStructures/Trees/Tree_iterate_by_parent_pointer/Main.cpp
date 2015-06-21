#include <iostream> // pause

#include "RunAllTests.h"

using namespace std;

void WaitUserEnter()
{
	system("pause");
}

int main()
{
	RunAllTests();

	WaitUserEnter();

	return 0;
}