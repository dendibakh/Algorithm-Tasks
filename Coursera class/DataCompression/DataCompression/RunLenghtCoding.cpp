#include "RunLenghtCoding.h"

namespace RunLeghtCoding
{
	compressedResult compress(const std::string& text)
	{
		compressedResult retVect;
		if (text.empty())
			return retVect;

		const char* data = text.data();
		size_t lenght = text.size();

		bool firstBit = ((*data) >> 7) & 1;
		retVect.push_back(firstBit); // store first bit. It will be used in expand.
		bool currentBitInSequence = firstBit;
		TypeOfTheCounter counter = 0;
		for (size_t i = 0; i < lenght; ++i)
		{
			for (short j = 7; j >= 0; --j)
			{
				bool currentBit = ( (*data) >> j ) & 1;
				if (currentBitInSequence != currentBit)
				{
					retVect.push_back(counter);
					counter = 1;
					currentBitInSequence = currentBit;
				}
				else
				{
					++counter;
				}
			}
			++data;
		}
		
		retVect.push_back(counter);
		return retVect;
	}
	
	// ToDo: remove code duplication
	compressedResult compress(const std::vector<bool>& text)
	{
		compressedResult retVect;
		if (text.empty())
			return retVect;

		retVect.push_back(*text.begin()); // store first bit. It will be used in expand.

		std::vector<bool>::const_iterator iter = text.begin();
		bool currentBit = *iter;
		TypeOfTheCounter counter = 1;
		for (++iter; iter != text.end(); ++iter)
		{
			if (currentBit != *iter)
			{
				retVect.push_back(counter);
				counter = 1;
				currentBit = *iter;
			}
			else
			{
				++counter;
			}
		}
		retVect.push_back(counter);
		return retVect;
	}

	std::vector<bool> expand(const compressedResult& compressedText)
	{
		std::vector<bool> retVect;
		if (compressedText.empty())
			return retVect;
		compressedResult::const_iterator iter = compressedText.begin();
		bool bit = (*iter);
		for (++iter; iter != compressedText.end(); ++iter)
		{
			for (TypeOfTheCounter counter = *iter; counter > 0; --counter)
			{
				retVect.push_back(bit);
			}
			bit = !bit;
		}
		return retVect;
	}
}