#include "BruteForceSubstringSearch.h"

BruteForceSubstringSearch::BruteForceSubstringSearch(const std::string& text) : text(text)
{

}

int BruteForceSubstringSearch::findSubString(const std::string& pattern)
{
	for (size_t i = 0; i < text.size(); ++i)
	{
		size_t j = 0;
		for ( ; j < pattern.size(); ++j)
		{
			if (text[i + j] != pattern[j])
				break;
		}
		if (j == pattern.size())
			return i;
	}
	return -1;
}