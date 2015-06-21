#pragma once
#include "WordNet.h"

class OutCast
{
public:
	OutCast(const WordNet& wNet);
	std::string findOutCast(const std::vector<std::string>& nouns);
private:
	const WordNet& wNet;
};