#include "TernarySearchTrie.h"
#include <algorithm>
#include <sstream>

TernarySearchTrie::Node::Node() : value(0), symbol(0), left(nullptr), equal(nullptr), right(nullptr)
{
}

TernarySearchTrie::TernarySearchTrie() : root(nullptr)
{
}

TernarySearchTrie::~TernarySearchTrie()
{
	clear();
}

void TernarySearchTrie::insert(const std::string& key, int value)
{
	insert(root, key, 0, value);
}

void TernarySearchTrie::insert(Node*& n, const std::string& key, size_t index, int value)
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

size_t TernarySearchTrie::height()
{
	return height(root, 0);
}

size_t TernarySearchTrie::height(Node* n, size_t level)
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

void TernarySearchTrie::clear()
{
	clear(root);
}

void TernarySearchTrie::clear(Node*& n)
{
	if (n)
	{
		clear(n->left);
		clear(n->equal);
		clear(n->right);
		delete n;
		n = nullptr;
	}
}

TernarySearchTrie::Node* TernarySearchTrie::find(Node* n, const std::string& key, size_t index)
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
	return nullptr;
}

bool TernarySearchTrie::exist(const std::string& key)
{
	Node *n = find(root, key, 0);
	if (!n)
		return false;
	return n->value != 0;
}

int TernarySearchTrie::getValue(const std::string& key)
{
	Node *n = find(root, key, 0);
	if (!n)
		throw std::runtime_error("Error occured while trying to get the value corresponding to the key: " + key + ". The key doesn't exist.");
	if (n->value == 0)
		throw std::runtime_error("Error occured while trying to get the value corresponding to the key: " + key + ". The key doesn't exist.");
	return n->value;
}

bool TernarySearchTrie::remove(Node*& n, const std::string& key, size_t index)
{
	if (n)
	{
		if (key[index] == n->symbol)
		{
			if (key.size() == index + 1)
			{
				if (n->value)
				{
					if (n->left || n->equal || n->right)
					{
						n->value = 0;
						return false; 
					}
					else
					{
						delete n;
						n = nullptr;
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

bool TernarySearchTrie::removeHelper(Node*& n, Node*& parent, const std::string& key, size_t index)
{
	if (remove(n, key, index))
	{
		if (parent->left || parent->equal || parent->right || parent->value)
		{
			delete parent;
			parent = nullptr;
			return true;
		}
	}
	return false;
}

void TernarySearchTrie::remove(const std::string& key)
{
	if (remove(root, key, 0))
	{
		delete root;
		root = nullptr;
	}
}

void TernarySearchTrie::putOneNodeInRows(Node* n, TrieRows& rows, size_t level)
{
	rows[level] += n->symbol;
	if (n->value)
	{
		std::stringstream stream;
		stream << "(" << n->value << ")";
		rows[level] += stream.str();
	}
	rows[level] += " ";
}

void TernarySearchTrie::getLeftTraversal(Node* n, TrieRows& rows, size_t level)
{
	if (n)
	{
		getLeftTraversal(n->left, rows, level);

		putOneNodeInRows(n, rows, level);

		getLeftTraversal(n->equal, rows, level + 1);
		getLeftTraversal(n->right, rows, level);
	}
}

std::string TernarySearchTrie::getLeftTraversal()
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

TernarySearchTrie::ListOfKeys TernarySearchTrie::getKeysWithPrefix(const std::string& prefix)
{
	ListOfKeys keys;
	Node* n = find(root, prefix, 0);
	if (!n)
		return keys;
	if (n->value)
		keys.push_back(prefix);
	collectKeys(n->equal, prefix, keys);
	return keys;
}

TernarySearchTrie::ListOfKeys TernarySearchTrie::collectAllKeys()
{
	ListOfKeys keys;
	collectKeys(root, "", keys);
	return keys;
}

void TernarySearchTrie::collectKeys(Node* n, std::string prefix, ListOfKeys& keys)
{
	if (n)
	{
		if (n->value)
			keys.push_back(prefix + n->symbol);
		collectKeys(n->left, prefix, keys);
		collectKeys(n->equal, prefix + n->symbol, keys);
		collectKeys(n->right, prefix, keys);
	}
}

TernarySearchTrie::ListOfKeys TernarySearchTrie::collectKeysThatMatch(const std::string& wildCard)
{
	ListOfKeys matches;
	findWildCard(root, wildCard, 0, matches, "");
	return matches;
}

void TernarySearchTrie::findWildCard(Node* n, const std::string& wildCard, size_t index, ListOfKeys& matches, std::string prefix)
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
					if (n->value)
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

std::string TernarySearchTrie::getLongestKeyWithPrefix(const std::string& prefix)
{
	int longestKeyLength = 0;
	findLongestKeyWithPrefix(root, prefix, 0, longestKeyLength);
	return prefix.substr(0, longestKeyLength);
}

void TernarySearchTrie::findLongestKeyWithPrefix(Node* n, const std::string& prefix, size_t index, int& longestKeyLength)
{
	if (n)
	{
		if ((prefix[index] == n->symbol))
		{
			if (n->value != 0)
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