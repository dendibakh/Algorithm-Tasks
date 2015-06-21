#include "OutCast.h"

OutCast::OutCast(const WordNet& wNet) : wNet(wNet)
{
}

std::string OutCast::findOutCast(const std::vector<std::string>& nouns)
{
	std::string retStr;
	int maxLength = 0;
	std::vector<std::vector<int>> memoize(nouns.size(), std::vector<int>(nouns.size(), 0));
	for (auto i = nouns.begin(); i != nouns.end(); ++i)
	{
		int totalLenght = 0;
		int x = i - nouns.begin();
		for (auto j = nouns.begin(); j != nouns.end(); ++j)
		{
			if (i != j)
			{
				int y = j - nouns.begin();
				if (memoize[x][y])
				{
					totalLenght += memoize[x][y];
				}
				else
				{
					int add = wNet.getDistance(*i, *j);
					totalLenght += add;
					memoize[x][y] = add; 
				}
			}
		}
		if (maxLength < totalLenght)
		{
			maxLength = totalLenght;
			retStr = *i;
		}
	}
	return retStr;
}