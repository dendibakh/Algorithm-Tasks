#include "BoyerMooreSubStringSearch.h"
#include <algorithm>

BoyerMooreSubstringSearch::BoyerMooreSubstringSearch(const std::string& text) : text(text)
{

}

void BoyerMooreSubstringSearch::precomuteRight(const std::string& pattern)
{
	right.clear();
	right.resize(radix);
	for (std::vector<int>::iterator iter = right.begin(); iter != right.end(); ++iter)
	{
		*iter = -1;
	}
	for (size_t i = 0; i < pattern.size(); ++i)
	{
		right[pattern[i]] = i;
	}
}

int BoyerMooreSubstringSearch::findSubString(const std::string& pattern)
{
	precomuteRight(pattern);
	size_t patSize = pattern.size();
	size_t textSize = text.size();
	int skip = 0;
	for (size_t i = 0; i <= textSize - patSize; i += skip)
	{
		skip = 0;
		for (int j = patSize - 1; j >= 0; --j)
		{
			if (pattern[j] != text[i + j])
			{
				skip = std::max(1, j - right[text[i + j]]);
				break;
			}
		}
		if (0 == skip)
			return i;
	}
	return -1;
}