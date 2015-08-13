#pragma once
#include <vector>
#include "CircullarIndexString.h"

typedef std::vector<CircullarIndexString> CircullarIndexStrSet;

CircullarIndexStrSet ThreeWayRadixQuickSort(const CircullarIndexStrSet& set);
void ThreeWayRadixQuickSort_NoConst(CircullarIndexStrSet& set);