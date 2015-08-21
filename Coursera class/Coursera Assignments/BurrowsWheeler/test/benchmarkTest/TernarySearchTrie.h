#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include <stdexcept>

template <class T>
class TernarySearchTrie
{
protected:
	struct Node
	{
		T value;
		char symbol;
		Node* left;
		Node* equal;
		Node* right;
		Node();
	};
public:
	typedef std::vector<std::string> ListOfKeys;
protected:
	virtual bool checkExistNodeByValue(T value) const;
	void insert(Node*& node, const std::string& key, size_t index, T value);
private:
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
protected:
	void findLongestKeyWithPrefix(Node* n, const std::string& prefix, size_t index, int& longestKeyLength);
public:
	static const int radix = 256; // static_cast<int>(std::pow(2, 8 * sizeof(char))); // amount of possible values
	static const char wildCardSymbol = '.';
	TernarySearchTrie();
	virtual ~TernarySearchTrie();
	void insert(const std::string& key, T value);
	T getValue(const std::string& key);
	bool exist(const std::string& key);
	void remove(const std::string& key);
	std::string getLeftTraversal();
	size_t height();
	void clear();

	ListOfKeys collectAllKeys();
	ListOfKeys getKeysWithPrefix(const std::string& prefix);
	ListOfKeys collectKeysThatMatch(const std::string& wildCard);
	std::string getLongestKeyWithPrefix(const std::string& prefix);
protected:
	Node* root;
};

template <class T>
TernarySearchTrie<T>::Node::Node() : value(0), symbol(0), left(0), equal(0), right(0)
{
}

template <class T>
TernarySearchTrie<T>::TernarySearchTrie() : root(0)
{
}

template <class T>
TernarySearchTrie<T>::~TernarySearchTrie()
{
	clear();
}

template <class T>
void TernarySearchTrie<T>::insert(const std::string& key, T value)
{
	insert(root, key, 0, value);
}

template <class T>
void TernarySearchTrie<T>::insert(Node*& n, const std::string& key, size_t index, T value)
{
	if (n)
	{
		if (key[index] == n->symbol)
		{
			if (key.size() == index + 1)
				n->value = value;
			else
				insert(n->equal, key, index + 1, value);
		}
		else if (key[index] > n->symbol)
		{
			insert(n->right, key, index, value);
		}
		else if (key[index] < n->symbol)
		{
			insert(n->left, key, index, value);
		}
	}
	else
	{
		n = new Node;
		n->symbol = key[index];
		if (key.size() == index + 1)
			n->value = value;
		else
			insert(n->equal, key, index + 1, value);
	}
}

template <class T>
size_t TernarySearchTrie<T>::height()
{
	return height(root, 0);
}

template <class T>
size_t TernarySearchTrie<T>::height(Node* n, size_t level)
{
	if (n)
	{
		int leftHeight = height(n->left, level) - 1; // it doesn't means new level
		int equalHeight = height(n->equal, level);
		int rightHeight = height(n->right, level) - 1; // it doesn't means new level
		int max = std::max(leftHeight, equalHeight);
		max = std::max(max, rightHeight);
		return level + max + 1;
	}
	return 0;
}

template <class T>
void TernarySearchTrie<T>::clear()
{
	clear(root);
}

template <class T>
void TernarySearchTrie<T>::clear(Node*& n)
{
	if (n)
	{
		clear(n->left);
		clear(n->equal);
		clear(n->right);
		delete n;
		n = 0;
	}
}

template <class T>
typename TernarySearchTrie<T>::Node* TernarySearchTrie<T>::find(Node* n, const std::string& key, size_t index)
{
	if (n)
	{
		if (key[index] == n->symbol)
		{
			if (key.size() == index + 1)
				return n;
			else
				return find(n->equal, key, index + 1);
		}
		else if (key[index] > n->symbol)
		{
			return find(n->right, key, index);
		}
		else if (key[index] < n->symbol)
		{
			return find(n->left, key, index);
		}
	}
	return 0;
}

template <class T>
bool TernarySearchTrie<T>::exist(const std::string& key)
{
	Node *n = find(root, key, 0);
	if (!n)
		return false;
	return checkExistNodeByValue(n->value);
}

template <class T>
bool TernarySearchTrie<T>::checkExistNodeByValue(T value) const
{
	return value != 0;
}

template <class T>
T TernarySearchTrie<T>::getValue(const std::string& key)
{
	Node *n = find(root, key, 0);
	if (!n)
		throw std::runtime_error("Error occured while trying to get the value corresponding to the key: " + key + ". The key doesn't exist.");
	if (!checkExistNodeByValue(n->value))
		throw std::runtime_error("Error occured while trying to get the value corresponding to the key: " + key + ". The key doesn't exist.");
	return n->value;
}

template <class T>
bool TernarySearchTrie<T>::remove(Node*& n, const std::string& key, size_t index)
{
	if (n)
	{
		if (key[index] == n->symbol)
		{
			if (key.size() == index + 1)
			{
				if (checkExistNodeByValue(n->value))
				{
					if (n->left || n->equal || n->right)
					{
						n->value = 0;
						return false;
					}
					else
					{
						delete n;
						n = 0;
						return true;
					}
				}
				else
				{
					throw std::runtime_error("Error occured while trying to get the value corresponding to the key: " + key + ". The key doesn't exist.");
				}
			}
			else
			{
				return removeHelper(n->equal, n, key, index + 1);
			}
		}
		else if (key[index] > n->symbol)
		{
			return removeHelper(n->right, n, key, index);
		}
		else if (key[index] < n->symbol)
		{
			return removeHelper(n->left, n, key, index);
		}
	}
	throw std::runtime_error("Error occured while trying to get the value corresponding to the key: " + key + ". The key doesn't exist.");
}

template <class T>
bool TernarySearchTrie<T>::removeHelper(Node*& n, Node*& parent, const std::string& key, size_t index)
{
	if (remove(n, key, index))
	{
		if (parent->left || parent->equal || parent->right || checkExistNodeByValue(parent->value))
		{
			delete parent;
			parent = 0;
			return true;
		}
	}
	return false;
}

template <class T>
void TernarySearchTrie<T>::remove(const std::string& key)
{
	if (remove(root, key, 0))
	{
		delete root;
		root = 0;
	}
}

template <class T>
void TernarySearchTrie<T>::putOneNodeInRows(Node* n, TrieRows& rows, size_t level)
{
	rows[level] += n->symbol;
	if (checkExistNodeByValue(n->value))
	{
		std::stringstream stream;
		stream << "(" << n->value << ")";
		rows[level] += stream.str();
	}
	rows[level] += " ";
}

template <class T>
void TernarySearchTrie<T>::getLeftTraversal(Node* n, TrieRows& rows, size_t level)
{
	if (n)
	{
		getLeftTraversal(n->left, rows, level);

		putOneNodeInRows(n, rows, level);

		getLeftTraversal(n->equal, rows, level + 1);
		getLeftTraversal(n->right, rows, level);
	}
}

template <class T>
std::string TernarySearchTrie<T>::getLeftTraversal()
{
	size_t h = height();
	TrieRows rows(h);
	getLeftTraversal(root, rows, 0);
	std::string str;
	for (TrieRows::const_iterator iter = rows.begin(); iter != rows.end(); ++iter)
	{
		str += *iter;
		str += "\n";
	}
	return str;
}

template <class T>
typename TernarySearchTrie<T>::ListOfKeys TernarySearchTrie<T>::getKeysWithPrefix(const std::string& prefix)
{
	ListOfKeys keys;
	Node* n = find(root, prefix, 0);
	if (!n)
		return keys;
	if (checkExistNodeByValue(n->value))
		keys.push_back(prefix);
	collectKeys(n->equal, prefix, keys);
	return keys;
}

template <class T>
typename TernarySearchTrie<T>::ListOfKeys TernarySearchTrie<T>::collectAllKeys()
{
	ListOfKeys keys;
	collectKeys(root, "", keys);
	return keys;
}

template <class T>
void TernarySearchTrie<T>::collectKeys(Node* n, std::string prefix, ListOfKeys& keys)
{
	if (n)
	{
		if (checkExistNodeByValue(n->value))
			keys.push_back(prefix + n->symbol);
		collectKeys(n->left, prefix, keys);
		collectKeys(n->equal, prefix + n->symbol, keys);
		collectKeys(n->right, prefix, keys);
	}
}

template <class T>
typename TernarySearchTrie<T>::ListOfKeys TernarySearchTrie<T>::collectKeysThatMatch(const std::string& wildCard)
{
	ListOfKeys matches;
	findWildCard(root, wildCard, 0, matches, "");
	return matches;
}

template <class T>
void TernarySearchTrie<T>::findWildCard(Node* n, const std::string& wildCard, size_t index, ListOfKeys& matches, std::string prefix)
{
	if (n)
	{
		if (wildCard[index] == wildCardSymbol)
		{
			if (wildCard.size() == index + 1)
			{
				collectKeys(n, prefix, matches);
			}
			else
			{
				findWildCard(n->left, wildCard, index, matches, prefix);
				findWildCard(n->equal, wildCard, index + 1, matches, prefix + n->symbol);
				findWildCard(n->right, wildCard, index, matches, prefix);
			}
		}
		else
		{
			if ((wildCard[index] == n->symbol))
			{
				if (wildCard.size() == index + 1)
				{
					if (checkExistNodeByValue(n->value))
						matches.push_back(prefix + n->symbol);
					collectKeys(n->equal, prefix + n->symbol, matches);
				}
				else
				{
					findWildCard(n->equal, wildCard, index + 1, matches, prefix + n->symbol);
				}
			}
			else if (wildCard[index] > n->symbol)
			{
				findWildCard(n->right, wildCard, index, matches, prefix);
			}
			else if (wildCard[index] < n->symbol)
			{
				findWildCard(n->left, wildCard, index, matches, prefix);
			}
		}
	}
}

template <class T>
std::string TernarySearchTrie<T>::getLongestKeyWithPrefix(const std::string& prefix)
{
	int longestKeyLength = 0;
	findLongestKeyWithPrefix(root, prefix, 0, longestKeyLength);
	return prefix.substr(0, longestKeyLength);
}

template <class T>
void TernarySearchTrie<T>::findLongestKeyWithPrefix(Node* n, const std::string& prefix, size_t index, int& longestKeyLength)
{
	if (n)
	{
		if ((prefix[index] == n->symbol))
		{
			if (checkExistNodeByValue(n->value))
				longestKeyLength = index + 1;
			if (prefix.size() > index + 1)
				findLongestKeyWithPrefix(n->equal, prefix, index + 1, longestKeyLength);
		}
		else if (prefix[index] > n->symbol)
		{
			findLongestKeyWithPrefix(n->right, prefix, index, longestKeyLength);
		}
		else if (prefix[index] < n->symbol)
		{
			findLongestKeyWithPrefix(n->left, prefix, index, longestKeyLength);
		}
	}
}

class LZW_TST : public TernarySearchTrie<unsigned int>
{
	virtual bool checkExistNodeByValue(unsigned int value) const;
public:
	LZW_TST();
	virtual ~LZW_TST();

	void insert(const std::string& key);
	void skipOneNumberForEndOfTheMessage();
	std::string getLongestKeyWithPrefix(const std::string& prefix, size_t beginIndex);
private:
	unsigned int incValue;
};

typedef TernarySearchTrie<int> TernarySearchTrieInt;
