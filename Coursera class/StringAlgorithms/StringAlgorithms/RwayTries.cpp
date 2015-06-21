#include "RwayTries.h"
#include <algorithm>
#include <sstream>

RwayTrie::Node::Node() : value(0), nodes(nullptr)
{
}

RwayTrie::RwayTrie() : root(nullptr)
{
}

RwayTrie::~RwayTrie()
{
   clear();
}

void RwayTrie::insert(const std::string& key, int value)
{
	if (!root)
		root = new Node;
	insert(root, key, 0, value);
}

void RwayTrie::insert(Node* node, const std::string& key, size_t index, int value)
{
	if (key.size() == index)
	{
		node->value = value;
		return;
	}

	if (!node->nodes)
		node->nodes = new Node[RwayTrie::radix];

	insert(node->nodes + key[index], key, index + 1, value);
}

size_t RwayTrie::height()
{
	if (!root || !root->nodes)
      return 0;
   return height(root->nodes);
}

size_t RwayTrie::height(Node* node)
{
   size_t maxHeight = 0;
   for (size_t i = 0; i < RwayTrie::radix; ++i)
   {
	   if ((node + i)->nodes)
		   maxHeight = std::max(maxHeight, height((node + i)->nodes));
   }
   return maxHeight + 1;
}

void RwayTrie::clear()
{
	if (root)
	{
		clear(root->nodes);
		delete root;
		root = nullptr;
	}
}

void RwayTrie::clear(Node*& node)
{
   for (size_t i = 0; i < RwayTrie::radix; ++i)
   {
      if ((node + i)->nodes)
		  clear((node + i)->nodes);
   }
   delete [] node;
   node = nullptr;
}

bool RwayTrie::exist(Node* node, const std::string& key, size_t index)
{
	if (key.size() == index)
	{
		if (node->value > 0)
			return true;
		else 
			return false;
	}

	if ((node->nodes) && (node->nodes + key[index]))
	   return exist(node->nodes + key[index], key, index + 1);
	return false;
}

bool RwayTrie::exist(const std::string& key)
{
	if (root)
		return exist(root, key, 0);
	return false;
}

int RwayTrie::getValue(Node* node, const std::string& key, size_t index)
{
	if (key.size() == index)
	{
		if (node->value)
			return node->value;
		throw std::runtime_error("Error occured while trying to get the value corresponding to the key: " + key + ". The key doesn't exist.");
	}
	
	if ((node->nodes) && (node->nodes + key[index]))
		return getValue(node->nodes + key[index], key, index + 1);
	throw std::runtime_error("Error occured while trying to get the value corresponding to the key: " + key + ". The key doesn't exist.");
}

int RwayTrie::getValue(const std::string& key)
{
	if (!root)
		throw std::runtime_error("Error occured while trying to get the value corresponding to the key: " + key + ". The key doesn't exist.");
	return getValue(root, key, 0);
}

bool RwayTrie::remove(Node* node, const std::string& key, size_t index)
{
	if (key.size() == index)
	{
		node->value = 0;
		if (node->nodes)
			return false;
		return true;
	}
		
	if ((node->nodes) && (node->nodes + key[index]))
	{
		bool needFreeMemory = remove(node->nodes + key[index], key, index + 1);
		if (!needFreeMemory)
			return false;
		bool noNullLinkExists = false;
		for (size_t i = 0; i < RwayTrie::radix; ++i)
		{
			if ((node->nodes + i)->nodes)
			{
				if (i != key[index])
				{
					noNullLinkExists = true;
					break;
				}
			}
		}

		if (!noNullLinkExists)
		{
			delete[] node->nodes;
			node->nodes = nullptr;
			return true;
		}
		return false;
	}
	throw std::runtime_error("Error occured while trying to remove the value corresponding to the key: " + key + ". The key doesn't exist.");
}

void RwayTrie::remove(const std::string& key)
{
	if (!root)
		throw std::runtime_error("Error occured while trying to remove the value corresponding to the key: " + key + ". The key doesn't exist.");
	if (remove(root, key, 0))
	{
		delete root;
		root = nullptr;
	}
}

void RwayTrie::getLeftTraversal(Node* node, TrieRows& rows, size_t level)
{
	for (size_t i = 0; i < RwayTrie::radix; ++i)
	{
		if (((node + i)->nodes) || ((node + i)->value))
			rows[level] += static_cast<char> (i);

		if ((node + i)->value)
		{
			std::stringstream stream;
			stream << "(" << (node + i)->value << ")";
			rows[level] += stream.str();
		}
		
		if ( ((node + i)->nodes) || ((node + i)->value) )
		    rows[level] += " ";
		
		if ((node + i)->nodes)
			getLeftTraversal((node + i)->nodes, rows, level + 1);
	}
}

std::string RwayTrie::getLeftTraversal()
{
	if (!root || !root->nodes)
		return "";
	size_t h = height();
	TrieRows rows(h);
	getLeftTraversal(root->nodes, rows, 0);
	std::string str;
	for (TrieRows::const_iterator iter = rows.begin(); iter != rows.end(); ++iter)
	{
		str += *iter;
		str += "\n";
	}
	return str;
}