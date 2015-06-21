#include "KnuthMorrisPrattSubstringSearch.h"

KnuthMorrisPrattSubstringSearch::KnuthMorrisPrattSubstringSearch(const std::string& text) : text(text), kmsStateMachine(radix)
{
	
}

int KnuthMorrisPrattSubstringSearch::findSubString(const std::string& pattern)
{
	buildStateMachine(pattern);
	size_t textSize = text.size();
	size_t patSize = pattern.size();
	size_t i = 0;
	size_t j = 0;
	for (; i < textSize && j < patSize; ++i)
		j = kmsStateMachine[text[i]][j];
	if (j == patSize)
		return i - patSize;
	return -1;
}

void KnuthMorrisPrattSubstringSearch::buildStateMachine(const std::string& pattern)
{
	size_t patSize = pattern.size();
	for (KnuthMorrisPrattStateMachine::iterator i = kmsStateMachine.begin(); i != kmsStateMachine.end(); ++i)
	{
		i->clear();
		i->resize(patSize);
	}
	kmsStateMachine[pattern[0]][0] = 1;
	for (size_t X = 0, j = 1; j < patSize; ++j)
	{
		for (size_t c = 0; c < radix; ++c)
			kmsStateMachine[c][j] = kmsStateMachine[c][X];
		kmsStateMachine[pattern[j]][j] = j + 1;
		X = kmsStateMachine[pattern[j]][X];
	}
}