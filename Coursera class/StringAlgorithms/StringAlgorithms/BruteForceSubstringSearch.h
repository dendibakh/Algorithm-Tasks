#pragma once
#include <string>

class BruteForceSubstringSearch
{
public:
	BruteForceSubstringSearch(const std::string& text);
	int findSubString(const std::string& pattern);
private:
	std::string text;
};