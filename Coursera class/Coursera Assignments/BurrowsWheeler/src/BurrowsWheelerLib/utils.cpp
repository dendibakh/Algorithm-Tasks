#include "utils.h"

std::vector<bool> getBinaryRepresentation(char symbol)
{
	std::vector<bool> retVect;
	for (short j = 7; j >= 0; --j)
	{
		bool currentBit = (symbol >> j) & 1;
		retVect.push_back(currentBit);
	}
	return retVect;
}

char getSymbol(const std::vector<bool>& BinaryRepresentation)
{
	return getSymbol(BinaryRepresentation.begin(), BinaryRepresentation.end());
}

char getSymbol(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end)
{
	if (BinaryRepresentation_begin == BinaryRepresentation_end)
		return 0;
	if (BinaryRepresentation_end - BinaryRepresentation_begin != 8)
		return 0;

	char result = 0;
	for (short j = 0; j < 8; ++j)
	{
		result |= *(BinaryRepresentation_begin + j) << (7 - j);
	}
	return result;
}
