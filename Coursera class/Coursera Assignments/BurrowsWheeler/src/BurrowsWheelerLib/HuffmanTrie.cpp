#include "HuffmanTrie.h"
#include <algorithm>
#include <sstream>
#include "utils.h"

HuffmanTrie::Node::Node(char symbol, int freq) : symbol(symbol), freq(freq), left(0), right(0)
{
}

bool HuffmanTrie::Node::isLeaf() const
{
	return left == 0 && right == 0;
}

bool HuffmanTrie::Node::operator==(const Node& rhs) const
{
	return this->freq == rhs.freq;
}

HuffmanTrie::HuffmanTrie(Node* n) : root(n)
{
}

HuffmanTrie::~HuffmanTrie()
{
	clear();
}

void HuffmanTrie::clear()
{
	clear(root);
}

void HuffmanTrie::clear(Node*& n)
{
	if (n)
	{
		clear(n->left);
		clear(n->right);
		delete n;
		n = 0;
	}
}

size_t HuffmanTrie::height() const
{
	return height(root, 0);
}

size_t HuffmanTrie::height(Node* n, size_t level) const
{
	if (n)
	{
		int leftHeight = height(n->left, level);
		int rightHeight = height(n->right, level);
		return level + std::max(leftHeight, rightHeight) + 1;
	}
	return 0;
}

void HuffmanTrie::getLeftTraversal(Node* n, TrieRows& rows, size_t level) const
{
	if (n)
	{
		putOneNodeInRows(n, rows, level);
		getLeftTraversal(n->left, rows, level + 1);
		getLeftTraversal(n->right, rows, level + 1);
	}
}

void HuffmanTrie::putOneNodeInRows(Node* n, TrieRows& rows, size_t level) const
{
	rows[level] += n->symbol;
	if (n->symbol)
	{
		std::stringstream stream;
		stream << "(" << n->freq << ")";
		rows[level] += stream.str();
	}
	rows[level] += " ";
}

std::string HuffmanTrie::getLeftTraversal() const
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

void HuffmanTrie::release()
{
	root = 0;
}

std::auto_ptr<HuffmanTrie> HuffmanTrie::mergeWithTrie(HuffmanTrie& rhs)
{
	HuffmanTrie::Node* commonNode = new HuffmanTrie::Node(getDummySymbol(), this->root->freq + rhs.root->freq);
	commonNode->left = this->root;
	commonNode->right = rhs.root;
	this->release();
	rhs.release();
	return std::auto_ptr<HuffmanTrie>(createNewTrie(commonNode));
}

HuffmanTrie* HuffmanTrie::createNewTrie(HuffmanTrie::Node* node) const
{
	return new HuffmanTrie(node);
}

char HuffmanTrie::getDummySymbol() const
{
	return '\0';
}

size_t HuffmanTrie::getRootFrequency() const
{
	return root->freq;
}

HuffmanTrie::SymbolTable HuffmanTrie::getSymbolTable() const
{
	SymbolTable sbTable(radix);
	if (root->isLeaf())
		sbTable[root->symbol].push_back(0);
	else
		getSymbolTable(root, sbTable, std::vector<bool>());
	return sbTable;
}

void HuffmanTrie::getSymbolTable(Node* n, SymbolTable& sbTable, std::vector<bool> code) const
{
	if (n)
	{
		if (n->isLeaf())
		{
			sbTable[n->symbol] = code;
		}
		else
		{
			code.push_back(false);
			getSymbolTable(n->left, sbTable, code);
			code.pop_back();
			code.push_back(true);
			getSymbolTable(n->right, sbTable, code);
		}
	}
}

std::string HuffmanTrie::expand(const compressedResult& comrText) const
{
	std::string result;
	if (root->isLeaf())
	{
		result.append(comrText.size(), root->symbol);
	}
	else
	{
	        compressedResult::const_iterator iter = comrText.begin();
	        compressedResult::const_iterator endIter = comrText.end();
	        while ( iter != endIter )
	        {
		    expand(root, iter, endIter, result);
		}
	}
	return result;
}

void HuffmanTrie::expand(Node* n, compressedResult::const_iterator& iter, const compressedResult::const_iterator& endIter, std::string& result) const
{
	if (n)
	{
		if (n->isLeaf())
		{
			result += n->symbol;
		}
		else if (iter != endIter)
		{
			if (*iter == true)
			{
				expand(n->right, ++iter, endIter, result);
			}
			else if (*iter == false)
			{
				expand(n->left, ++iter, endIter, result);
			}
		}
	}
}

HuffmanTrie::compressedResult HuffmanTrie::serializeTrie() const
{
	compressedResult result;
	serializeTrie(root, result);
	return result;
}

void HuffmanTrie::serializeTrie(Node* n, compressedResult& result) const
{
	if (n)
	{
		if (n->isLeaf())
		{
			result.push_back(true);
			std::vector<bool> binSymbol = getBinaryRepresentation(n->symbol);
			result.insert(result.end(), binSymbol.begin(), binSymbol.end());
		}
		else
		{
			result.push_back(false);
			serializeTrie(n->left, result);
			serializeTrie(n->right, result);
		}
	}
}

void HuffmanTrie::constructFromBinaryRepresentation(Node*& n, compressedResult::const_iterator& iter, const compressedResult::const_iterator& endIter)
{
	if (iter == endIter)
		return;
	if (*iter == false)
	{
		n = new Node(getDummySymbol(), 0);
		++iter;
		constructFromBinaryRepresentation(n->left, iter, endIter);
		constructFromBinaryRepresentation(n->right, iter, endIter);
	}
	else
	{
		++iter;
		n = new Node(getSymbol(iter, iter + 8), 0);
		iter = iter + 8;
	}
}

HuffmanTrie::compressedResult::const_iterator HuffmanTrie::constructFromBinaryRepresentation(const compressedResult& trieBinRep)
{
	HuffmanTrie::compressedResult::const_iterator iter = trieBinRep.begin();
	constructFromBinaryRepresentation(root, iter, trieBinRep.end());
	return iter;
}
