#pragma once
#include <string>
#include <vector>

class TernarySearchTrie
{
	struct Node
	{
		int value;
		char symbol;
		Node* left;
		Node* equal;
		Node* right;
		Node();
	};
public:
	typedef std::vector<std::string> ListOfKeys;
private:
	void insert(Node*& node, const std::string& key, size_t index, int value);
	bool remove(Node*& node, const std::string& key, size_t index);
	bool removeHelper(Node*& node, Node*& parent, const std::string& key, size_t index);
	Node* find(Node* node, const std::string& key, size_t index);
	size_t height(Node* node, size_t level);
	void clear(Node*& node);

	typedef std::vector<std::string> TrieRows;
	void putOneNodeInRows(Node* node, TrieRows& rows, size_t level);
	void getLeftTraversal(Node* node, TrieRows& rows, size_t level);

	void collectKeys(Node* node, std::string prefix, ListOfKeys& keys);
	void findWildCard(Node* node, const std::string& key, size_t index, ListOfKeys& matches, std::string prefix);
	void findLongestKeyWithPrefix(Node* n, const std::string& prefix, size_t index, int& longestKeyLength);
public:
	static const int radix = 256; // static_cast<int>(std::pow(2, 8 * sizeof(char))); // amount of possible values
	static const char wildCardSymbol = '.';
	TernarySearchTrie();
	~TernarySearchTrie();
	void insert(const std::string& key, int value);
	int getValue(const std::string& key);
	bool exist(const std::string& key);
	void remove(const std::string& key);
	std::string getLeftTraversal();
	size_t height();
	void clear();

	ListOfKeys collectAllKeys();
	ListOfKeys getKeysWithPrefix(const std::string& prefix);
	ListOfKeys collectKeysThatMatch(const std::string& wildCard);
	std::string getLongestKeyWithPrefix(const std::string& prefix);
private:
	Node* root;
};