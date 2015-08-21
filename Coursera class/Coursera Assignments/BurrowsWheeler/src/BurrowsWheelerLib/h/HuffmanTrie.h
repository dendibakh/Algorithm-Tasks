#pragma once
#include <string>
#include <vector>
#include <memory>

// This is prefix-free coding algorithm!
class HuffmanTrie
{
public:
	struct Node
	{
		char symbol;
		int freq;
		Node* left;
		Node* right;
		Node(char symbol, int freq);
		bool isLeaf() const;
		bool operator==(const Node& rhs) const;
	};

	typedef std::vector<std::vector<bool> > SymbolTable;
	typedef std::vector<bool> compressedResult;

private: // implementation details
	void clear(Node*& n);
	size_t height(Node* n, size_t level) const;
	
	typedef std::vector<std::string> TrieRows;
	void putOneNodeInRows(Node* node, TrieRows& rows, size_t level) const;
	void getLeftTraversal(Node* n, TrieRows& rows, size_t level) const;

	void getSymbolTable(Node* n, SymbolTable& sbTable, std::vector<bool> code) const;
	void expand(Node* n, compressedResult::const_iterator& iter, const compressedResult::const_iterator& endIter, std::string& result) const;
	void serializeTrie(Node* n, compressedResult& result) const;
	void constructFromBinaryRepresentation(Node*& n, compressedResult::const_iterator& iter, const compressedResult::const_iterator& endIter);

	void release();

	HuffmanTrie(const HuffmanTrie& rhs);// = delete;
	HuffmanTrie& operator=(const HuffmanTrie& rhs);// = delete;
public:
	HuffmanTrie(Node* n);
	virtual ~HuffmanTrie();
	
	static const unsigned short radix = 256; // static_cast<int>(std::pow(2, 8 * sizeof(char))); // amount of possible values

	std::string getLeftTraversal() const;
	std::auto_ptr<HuffmanTrie> mergeWithTrie(HuffmanTrie& rhs);
	size_t height() const;
	void clear();
	size_t getRootFrequency() const;

	SymbolTable getSymbolTable() const;
	compressedResult serializeTrie() const;
	std::string expand(const compressedResult& comrText) const;

	compressedResult::const_iterator constructFromBinaryRepresentation(const compressedResult& trieBinRep);

protected: // for test purposes
	virtual char getDummySymbol() const;
	virtual HuffmanTrie* createNewTrie(HuffmanTrie::Node* node) const;
private:
	Node* root;
};
