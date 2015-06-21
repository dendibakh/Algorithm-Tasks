#include "RabinKarpSubStringSearch.h"

RabinKarpSubStringSearch::RabinKarpSubStringSearch(const std::string& text) : text(text)
{

}

size_t RabinKarpSubStringSearch::hash(const std::string& key, size_t M)
{
	size_t h = 0;
	for (int j = 0; j < M; ++j)
		h = (radix * h + key[j]) % Q;
	return h;
}

int RabinKarpSubStringSearch::findSubString(const std::string& pattern)
{
	size_t patSize = pattern.size();
	size_t textSize = text.size();
	size_t multiplier = computeMultiplier(patSize);
	size_t patHash = computePatternHash(pattern);
	size_t txtHash = hash(text, patSize);
	if (txtHash == patHash)
		return 0;
	for (size_t i = patSize; i < textSize; ++i)
	{
		// remove leading character and compute hash 
		txtHash = (txtHash + Q - multiplier * text[i - patSize] % Q) % Q;
		// add trailing character and compute hash
		txtHash = (txtHash * radix + text[i]) % Q;
		if (txtHash == patHash)
			return i - patSize + 1;
	}
	return -1;
}

size_t RabinKarpSubStringSearch::computeMultiplier(size_t M)
{
	size_t multiplier = 1;
	for (size_t i = 1; i <= M - 1; ++i)
		multiplier = (radix * multiplier) % Q;
	return multiplier;
}

size_t RabinKarpSubStringSearch::computePatternHash(const std::string& pattern)
{
	return hash(pattern, pattern.size());
}