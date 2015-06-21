#pragma once
#include <string>
#include "IndexString.h"
#include "3WayRadixQuickSort.h"

class KeywordInContextSearch
{
	size_t binarySearch_leftBorder(const std::string& str, size_t SymbolIndex, size_t left, size_t right) const;
	size_t binarySearch_rightBorder(const std::string& str, size_t SymbolIndex, size_t left, size_t right) const;
public:
	KeywordInContextSearch(std::string& context);
	bool findString(const std::string& context) const;
	size_t getAmountOfStringOccurences(const std::string& context) const;
	std::vector<size_t> findStringOccurences(const std::string& context) const;
private:
	IndexStrSet suffixArray;
	//StrSet suffixArrayStr; //for debugging purposes
};