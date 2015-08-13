#include <iostream>
#include "3WayRadixQuickSort.h"

using namespace std;

namespace ThreeWayRadixQsort_modifiedKeyIndexCounting_IndexStr
{
	void exchange(CircullarIndexStrSet& set, int pos1, int pos2)
	{
		CircullarIndexString temp(set[pos1]);
		set[pos1] = set[pos2];
		set[pos2] = temp;
	}

	void DoSort(CircullarIndexStrSet& set, size_t digitIndex, int lo, int hi)
	{
		if (hi <= lo) // condition to break the recursion
			return;

		int lo_copy = lo;
		int hi_copy = hi;

		unsigned char symbolIndex = set[lo_copy][digitIndex];
		int i = lo_copy + 1;
		while (i <= hi_copy)
		{
			unsigned char curSymbolIndex = set[i][digitIndex];
			if (symbolIndex > curSymbolIndex)
			{
				exchange(set, lo_copy, i);
				++i;
				++lo_copy;
			}
			else if (curSymbolIndex > symbolIndex)
			{
				exchange(set, hi_copy, i);
				--hi_copy;
			}
			else
			{
				++i;
			}
		}

		DoSort(set, digitIndex, lo, lo_copy - 1);
		DoSort(set, digitIndex + 1, lo_copy, hi_copy);
		DoSort(set, digitIndex, hi_copy + 1, hi);
	}
}

CircullarIndexStrSet ThreeWayRadixQuickSort(const CircullarIndexStrSet& set)
{
	using namespace ThreeWayRadixQsort_modifiedKeyIndexCounting_IndexStr;
	CircullarIndexStrSet retSet(set);
	DoSort(retSet, 0, 0, retSet.size() - 1);
	return retSet;
}

void ThreeWayRadixQuickSort_NoConst(CircullarIndexStrSet& set)
{
	using namespace ThreeWayRadixQsort_modifiedKeyIndexCounting_IndexStr;
	DoSort(set, 0, 0, set.size() - 1);
}