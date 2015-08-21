#include "LZWCompression.h"

void LZWCompression::fillTrieWithRadixSymbols()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(LZW_TST::radix); ++i)
	{
		char c = static_cast<char>(i);
		trie->insert(std::string(1, c));
	}
}

LZWCompression::LZWCompression()
{

}

LZWCompression::~LZWCompression()
{

}

LZWCompression::compressedResult LZWCompression::getCompressedResult(const std::string& text)
{
	compressedResult retVect;
	if (text.empty())
		return retVect;

	trie.reset(new LZW_TST());
	fillTrieWithRadixSymbols();
	trie->skipOneNumberForEndOfTheMessage();

	size_t textSize = text.size();
	for (size_t i = 0; i < textSize;)
	{
		std::string longestPrefix = trie->getLongestKeyWithPrefix(text, i);
		size_t lenght = longestPrefix.size();
		retVect.push_back(trie->getValue(longestPrefix));
		if ((lenght < textSize))
			trie->insert(text.substr(i, lenght + 1));
		i += lenght;
	}

	retVect.push_back(LZW_TST::radix);
	return retVect;
}

std::string LZWCompression::getExpandedResult(const compressedResult& compressedText)
{
	std::string retText;
	if (compressedText.empty())
		return retText;

	symbTable.reset(new SymbolTable(LZW_TST::radix));
	fillSymbolTable();
	(*symbTable).push_back("");
	
	compressedResult::const_iterator iter = compressedText.begin();
	retText += (*symbTable)[*iter];
	++iter;
	for (; iter != compressedText.end() && *iter != static_cast<unsigned int>(LZW_TST::radix); ++iter)
	{
		if (*iter > static_cast<unsigned int>(symbTable->size()))
		{
			throw std::runtime_error("Expander: error while expanding compressed text.");
		}
		else if (static_cast<unsigned int>(*iter) == symbTable->size())
		{
			(*symbTable).push_back((*symbTable)[*(iter - 1)] + (*symbTable)[*(iter - 1)][0]);
		}
		else
		{
			(*symbTable).push_back((*symbTable)[*(iter - 1)] + (*symbTable)[*(iter)][0]);
		}
		retText += (*symbTable)[*iter];
	}
	
	if (iter == compressedText.end())
		throw std::runtime_error("Expander: incorrect format of the compressed text.");
	
	return retText;
}

void LZWCompression::fillSymbolTable()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(LZW_TST::radix); ++i)
	{
		unsigned char c = static_cast<unsigned char>(i);
		(*symbTable)[c] = std::string(1, c);
	}
}
