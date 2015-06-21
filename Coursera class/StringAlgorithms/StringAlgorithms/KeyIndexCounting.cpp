#include "KeyIndexCounting.h"
#include <vector>

using namespace std;

namespace symbolTable
{
	const int symbolsCount = 6;
	size_t convertSymbolToIndex(char c)
	{
		switch (c)
		{
		case 'a':
			return 1;
		case 'b':
			return 2;
		case 'c':
			return 3;
		case 'd':
			return 4;
		case 'e':
			return 5;
		case 'f':
			return 6;
		}
		return 0;
	}
}

string KeyIndexCounting(const string& str)
{
	using namespace symbolTable;
	string retStr;
	
	std::vector<int> vect(symbolsCount + 1, 0);
	// count symbols appearance
	for (auto i = str.begin(); i != str.end(); ++i)
		vect[convertSymbolToIndex(*i)]++;

	// accumulate values
	for (auto i = vect.begin() + 1; i != vect.end(); ++i)
		*i += *(i - 1);

	// make sort string
	retStr.resize(str.length());
	for (auto i = str.begin(); i != str.end(); ++i)
	{
		size_t index = convertSymbolToIndex(*i) - 1;
		retStr[vect[index]] = *i;
		vect[index]++;
	}

	return retStr;
}