#include <iostream>
#include "MSDRadixSort.h"

using namespace std;

namespace
{
        void debugPrint(const StrSet& set)
        {
                for (StrSet::const_iterator i = set.begin(); i != set.end(); ++i)
                {
                        cout << *i << endl;
                }
        }

        void debugPrint(const std::vector<int>& set)
        {
                for (std::vector<int>::const_iterator i = set.begin(); i != set.end(); ++i)
                {
                        cout << *i << endl;
                }
        }
}

namespace MSD_modifiedKeyIndexCounting
{
        namespace symbolTable
        {
                const char firstASCISmallLetter = 96;
                const size_t symbolsCount = 26;
                size_t convertSymbolToIndex(char c)
                {
                        return (c - firstASCISmallLetter > 0) ? c - firstASCISmallLetter + 1 : 1; // here first cell is for null-terminator symbol at the end of the string
                }
        }

		using namespace symbolTable;

        void KeyIndexCounting(StrSet& set, size_t digitIndex, int lo, int hi)
        {
                if (hi <= lo) // condition to break the recursion
                        return;

				// idea: cut from the whole set only those strings, that will be considered.
				// And then just do KeyIndexCounting on that cutted set. But in the end we need to put back sorted strings in right position.
				// So we need to keep in mind offset "lo".

				StrSet tempSet;
				tempSet.resize(hi - lo + 1);
				for (int i = lo; i < hi + 1; ++i)
					tempSet[i - lo] = set[i];

                std::vector<int> vect(symbolsCount + 2, 0);

                // count symbols appearance
				for (int i = 0; i < hi - lo + 1; ++i)
					vect[convertSymbolToIndex(tempSet[i][digitIndex])]++;

                // accumulate values
                for (std::vector<int>::iterator i = vect.begin() + 1; i != vect.end(); ++i)
                        *i += *(i - 1);

                // make sort string
				std::vector<int> vect_copy(vect);
				for (int i = 0; i < hi - lo + 1; ++i)
                {
						size_t index = convertSymbolToIndex(tempSet[i][digitIndex]) - 1;
						set[vect[index] + lo] = tempSet[i];
                        vect[index]++;
                }

				// After sort first letter we begin sorting next symbol in those string, in which first letter are equal.
				// That information we already have in vect_copy. We know the intervals of each symbols.
				for (size_t i = 1; i < symbolsCount; ++i) 
					KeyIndexCounting(set, digitIndex + 1, vect_copy[i] + lo, vect_copy[i + 1] + lo - 1);
        }

        
}

using namespace MSD_modifiedKeyIndexCounting;

StrSet MostSignificantDigitSort(const StrSet& set)
{
	StrSet retSet(set);
	KeyIndexCounting(retSet, 0, 0, retSet.size() - 1);
	return retSet;
}