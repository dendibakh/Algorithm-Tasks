#pragma once 
#include <string>
#include <vector>

class KnuthMorrisPrattSubstringSearch
{
	typedef std::vector<std::vector<int>> KnuthMorrisPrattStateMachine;
	void buildStateMachine(const std::string& pattern);
public:
	static const int radix = 256; // static_cast<int>(std::pow(2, 8 * sizeof(char))); // amount of possible values
	KnuthMorrisPrattSubstringSearch(const std::string& text);
	int findSubString(const std::string& pattern);
private:
	KnuthMorrisPrattStateMachine kmsStateMachine;
	std::string text;
};