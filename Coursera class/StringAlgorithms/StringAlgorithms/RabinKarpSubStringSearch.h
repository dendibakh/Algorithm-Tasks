#pragma once 
#include <string>

class RabinKarpSubStringSearch
{
	size_t hash(const std::string& key, size_t M);
	size_t computePatternHash(const std::string& pattern);
	size_t computeMultiplier(size_t M);
public:
	static const int Q = 997; // big prime number
	static const int radix = 256; // static_cast<int>(std::pow(2, 8 * sizeof(char))); // amount of possible values
	RabinKarpSubStringSearch(const std::string& text);
	int findSubString(const std::string& pattern);
private:
	std::string text;
};