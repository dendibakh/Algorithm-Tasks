#pragma once

#include "HuffmanTrie.h"
#include <queue>

class HuffmanAlgorithm
{
public:
	typedef HuffmanTrie::compressedResult compressedResult;
private:
	virtual HuffmanTrie* createNewTrie(HuffmanTrie::Node* node) const;
	compressedResult compress(const std::string& text);
public:
	HuffmanAlgorithm();
	virtual ~HuffmanAlgorithm();
	
	compressedResult getCompressedResult(const std::string& text);
	std::string getExpandedResult(const compressedResult& compressedText);

protected: // for test purposes
	void countFrequencies(const std::string& text);
	void buildTrie(const std::string& text);
	compressedResult compressTextOnly(const std::string& text);
	std::string expandTextOnly(const compressedResult& compressedText);
	std::vector<size_t> freq;
	std::auto_ptr<HuffmanTrie> trie;
	HuffmanTrie::SymbolTable symbolTable;
};
