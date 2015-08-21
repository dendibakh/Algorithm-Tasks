#pragma once
#include "TernarySearchTrie.h"
#include <memory>

class LZWCompression
{
protected:
	void fillTrieWithRadixSymbols();

	typedef std::vector<std::string> SymbolTable;
	void fillSymbolTable();
public:
	typedef std::vector<unsigned int> compressedResult;

	LZWCompression();
	virtual ~LZWCompression();

	compressedResult getCompressedResult(const std::string& text);
	std::string getExpandedResult(const compressedResult& compressedText);

protected:
	std::auto_ptr<LZW_TST> trie;
	std::auto_ptr<SymbolTable> symbTable;
};
