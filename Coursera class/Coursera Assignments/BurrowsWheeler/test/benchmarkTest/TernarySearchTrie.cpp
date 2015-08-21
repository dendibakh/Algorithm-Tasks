#include "TernarySearchTrie.h"

LZW_TST::LZW_TST() : TernarySearchTrie<unsigned int>(), incValue(0)
{

}

LZW_TST::~LZW_TST()
{

}

void LZW_TST::insert(const std::string& key)
{
	unsigned int newValue = incValue + 1;
	if (newValue >= 1) // no overflow
	{
		TernarySearchTrie<unsigned int>::insert(root, key, 0, incValue);
		++incValue;
	}
}

void LZW_TST::skipOneNumberForEndOfTheMessage()
{
	++incValue;
}

bool LZW_TST::checkExistNodeByValue(unsigned int value) const
{
	return value >= 0;
}

std::string LZW_TST::getLongestKeyWithPrefix(const std::string& prefix, size_t beginIndex)
{
	int longestKeyLength = 0;
	TernarySearchTrie<unsigned int>::findLongestKeyWithPrefix(root, prefix, beginIndex, longestKeyLength);
	return prefix.substr(beginIndex, longestKeyLength - beginIndex);
}
