#include "KeywordInContextSearch.h"

KeywordInContextSearch::KeywordInContextSearch(std::string& context)
{
	size_t N = context.size();
	for (size_t i = 0; i < N; ++i)
		suffixArray.push_back(IndexString(context, i, N));

	ThreeWayRadixQuickSort_NoConst(suffixArray);

	//for debugging purposes
	//for (auto i = suffixArray.begin(); i != suffixArray.end(); ++i)
	//	suffixArrayStr.push_back(i->getString());
}

size_t KeywordInContextSearch::getAmountOfStringOccurences(const std::string& context) const
{
	return findStringOccurences(context).size();
}

bool KeywordInContextSearch::findString(const std::string& context) const
{
	return findStringOccurences(context).size() > 0;
}

std::vector<size_t> KeywordInContextSearch::findStringOccurences(const std::string& context) const
{
	std::vector<size_t> retVect;
	size_t N = suffixArray.size();
	size_t leftBorder = 0;
	size_t rightBorder = N - 1;

	for (std::string::const_iterator iter = context.begin(); iter != context.end(); ++iter)
	{
		size_t SymbolIndex = iter - context.begin();
		size_t new_leftBorder  = binarySearch_leftBorder (context, SymbolIndex, leftBorder, rightBorder);
		size_t new_rightBorder = binarySearch_rightBorder(context, SymbolIndex, leftBorder, rightBorder);
		if ((new_leftBorder >= N) || (new_rightBorder == 0) || (new_leftBorder > new_rightBorder))
		{
			return retVect;
		}
		else
		{
			leftBorder = new_leftBorder;
			rightBorder = new_rightBorder;
		}
	}

	for (size_t i = leftBorder; i <= rightBorder; ++i)
		retVect.push_back(suffixArray[i].getBegin());
	return retVect;
}

size_t KeywordInContextSearch::binarySearch_leftBorder(const std::string& str, size_t SymbolIndex, size_t left, size_t right) const
{
	if (suffixArray[left][SymbolIndex] == str[SymbolIndex])
		return left;

	size_t begin = left;
	size_t end = right;
	size_t N = suffixArray.size();
	size_t result = N - 1;
	while (begin <= end)
	{
		size_t mid = (begin + end) / 2;
		if (suffixArray[mid][SymbolIndex] < str[SymbolIndex])
		{
			begin = mid + 1;
			result = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}
		
	return result;
}

size_t KeywordInContextSearch::binarySearch_rightBorder(const std::string& str, size_t SymbolIndex, size_t left, size_t right) const
{
	if (suffixArray[right][SymbolIndex] == str[SymbolIndex])
		return right;

	size_t begin = left;
	size_t end = right;
	size_t N = suffixArray.size();
	size_t result = N - 1;
	while (begin <= end)
	{
		size_t mid = (begin + end) / 2;
		if (suffixArray[mid][SymbolIndex] <= str[SymbolIndex])
		{
			begin = mid + 1;
			result = mid;
		}
		else
		{
			end = mid - 1;
		}
	}

	return result;
}