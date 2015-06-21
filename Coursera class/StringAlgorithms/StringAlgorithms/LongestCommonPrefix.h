#pragma once
#include <string>
#include "IndexString.h"
#include "3WayRadixQuickSort.h"

class LongestCommonPrefix
{
	size_t defineLCP(const std::string& lhs, const std::string& rhs) const;
public:
	LongestCommonPrefix(std::string& context);
	std::string getResult() const;
private:
	std::string result;
	IndexStrSet suffixArray;
	StrSet suffixArrayStr; //for debugging purposes
};