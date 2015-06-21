#include "LongestCommonPrefix.h"
#include <algorithm>

LongestCommonPrefix::LongestCommonPrefix(std::string& context)
{
	size_t N = context.size();
	for (size_t i = 0; i < N; ++i)
		suffixArray.push_back(IndexString(context, i, N));

	ThreeWayRadixQuickSort_NoConst(suffixArray);

	//for debugging purposes
	for (auto i = suffixArray.begin(); i != suffixArray.end(); ++i)
		suffixArrayStr.push_back(i->getString());

	IndexStrSet::const_iterator i = suffixArray.begin();
	if (i != suffixArray.end())
		++i;
	for ( ; i != suffixArray.end(); ++i)
	{
		size_t current_lenght = defineLCP((i - 1)->getString(), i->getString());
		if (current_lenght > result.size())
			result = i->getString().substr(0, current_lenght);
	}
}

size_t LongestCommonPrefix::defineLCP(const std::string& lhs, const std::string& rhs) const
{
	size_t leftLenght = lhs.size();
	size_t rightLenght = rhs.size();
	size_t minLenght = std::min(leftLenght, rightLenght);
	size_t result = 0;
	for (size_t i = 0; i < minLenght; ++i)
	{
		if (lhs[i] != rhs[i])
			break;
		++result;
	}
	return result;
}

std::string LongestCommonPrefix::getResult() const
{
	return result;
}