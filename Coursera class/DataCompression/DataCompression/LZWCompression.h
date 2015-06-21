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
	typedef std::vector<short> compressedResult;

	LZWCompression();
	virtual ~LZWCompression();

	compressedResult getCompressedResult(const std::string& text);
	std::string getExpandedResult(const compressedResult& compressedText);

protected:
	std::unique_ptr<LZW_TST> trie;
	std::unique_ptr<SymbolTable> symbTable;
};