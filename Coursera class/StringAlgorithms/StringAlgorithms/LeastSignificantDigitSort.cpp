#include "LeastSignificantDigitSort.h"
//#include "KeyIndexCounting.h"

using namespace std;

namespace modifiedKeyIndexCounting
{
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

	StrSet KeyIndexCounting(const StrSet& set, size_t digitIndex)
	{
		using namespace symbolTable;
		StrSet retSet;

		std::vector<int> vect(symbolsCount + 1, 0);
		// count symbols appearance
		for (auto i = set.begin(); i != set.end(); ++i)
			vect[convertSymbolToIndex((*i)[digitIndex])]++;

		// accumulate values
		for (auto i = vect.begin() + 1; i != vect.end(); ++i)
			*i += *(i - 1);

		// make sort string
		retSet.resize(set.size());
		for (auto i = set.begin(); i != set.end(); ++i)
		{
			size_t index = convertSymbolToIndex((*i)[digitIndex]) - 1;
			retSet[vect[index]] = *i;
			vect[index]++;
		}

		return retSet;
	}
}

StrSet LeastSignificantDigitSort(const StrSet& set)
{
	using namespace modifiedKeyIndexCounting;
	StrSet retSet(set);
	for (size_t i = retSet[0].length(); i > 0; --i)
	{
		retSet = KeyIndexCounting(retSet, i - 1);
	}
	return retSet;
}