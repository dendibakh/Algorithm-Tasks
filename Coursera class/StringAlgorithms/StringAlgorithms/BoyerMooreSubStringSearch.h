#pragma once 
#include <string>
#include <vector>

class BoyerMooreSubstringSearch
{
	void precomuteRight(const std::string& pattern);
public:
	static const int radix = 256; // static_cast<int>(std::pow(2, 8 * sizeof(char))); // amount of possible values
	BoyerMooreSubstringSearch(const std::string& text);
	int findSubString(const std::string& pattern);
private:
	std::vector<int> right;
	std::string text;
};