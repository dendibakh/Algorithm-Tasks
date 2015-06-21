#pragma once

#include <vector>
#include <string>

namespace RunLeghtCoding
{
	typedef int TypeOfTheCounter;
	typedef std::vector<TypeOfTheCounter> compressedResult;
	compressedResult compress(const std::string& text);
	compressedResult compress(const std::vector<bool>& text);
	std::vector<bool> expand(const compressedResult& compressedText);
}
