#pragma once
#include <string>
#include <vector>
#include "IndexString.h"

typedef std::vector<std::string> StrSet;

StrSet ThreeWayRadixQuickSort(const StrSet& set);

typedef std::vector<IndexString> IndexStrSet;

IndexStrSet ThreeWayRadixQuickSort(const IndexStrSet& set);
void ThreeWayRadixQuickSort_NoConst(IndexStrSet& set);