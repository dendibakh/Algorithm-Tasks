#include "HuffmanCompression.h"

HuffmanAlgorithm::HuffmanAlgorithm() : trie(nullptr)
{

}

HuffmanAlgorithm::~HuffmanAlgorithm()
{

}

void HuffmanAlgorithm::buildTrie(const std::string& text)
{
	class HuffmanTrieComparison
	{
	public:
		typedef HuffmanTrie* Elem;
		bool operator() (const Elem& lhs, const Elem& rhs) const
		{
			return lhs->getRootFrequency() > rhs->getRootFrequency();
		}
	};

	std::priority_queue<HuffmanTrieComparison::Elem, std::vector<HuffmanTrieComparison::Elem>, HuffmanTrieComparison> pq;

	countFrequencies(text);
	for (size_t i = 0; i < HuffmanTrie::radix; ++i)
	{
		if (freq[i] > 0)
		{
			HuffmanTrie::Node* node = new HuffmanTrie::Node(i, freq[i]);
			pq.push(HuffmanTrieComparison::Elem(createNewTrie (node) ));
		}
	}

	while (pq.size() > 1)
	{
		HuffmanTrieComparison::Elem first = pq.top();
		pq.pop();
		HuffmanTrieComparison::Elem second = pq.top();
		pq.pop();
		pq.push(first->mergeWithTrie(*second).release());
	}

	trie.reset(pq.top());
	pq.pop();

	symbolTable = trie->getSymbolTable();
}

HuffmanTrie* HuffmanAlgorithm::createNewTrie(HuffmanTrie::Node* node) const
{
	return new HuffmanTrie(node);
}

void HuffmanAlgorithm::countFrequencies(const std::string& text)
{
	freq = std::vector<size_t>(HuffmanTrie::radix, 0);
	for (std::string::const_iterator i = text.begin(); i != text.end(); ++i)
	{
		++freq[*i];
	}
}

HuffmanAlgorithm::compressedResult HuffmanAlgorithm::compress(const std::string& text)
{
	compressedResult retVect;
	if (text.empty())
		return retVect;

	buildTrie(text);

	for (std::string::const_iterator i = text.begin(); i != text.end(); ++i)
	{
		retVect.insert(retVect.end(), symbolTable[*i].begin(), symbolTable[*i].end());
	}

	return retVect;
}

HuffmanAlgorithm::compressedResult HuffmanAlgorithm::compressTextOnly(const std::string& text)
{
	return compress(text);
}

HuffmanAlgorithm::compressedResult HuffmanAlgorithm::getCompressedResult(const std::string& text)
{
	HuffmanAlgorithm::compressedResult result = compress(text);
	HuffmanAlgorithm::compressedResult binTrie = trie->serializeTrie();
	result.insert(result.begin(), binTrie.begin(), binTrie.end());
	return result;
}

std::string HuffmanAlgorithm::expandTextOnly(const compressedResult& compressedText)
{
	std::string retText;
	if (compressedText.empty())
		return retText;

	return trie->expand(compressedText);
}

std::string HuffmanAlgorithm::getExpandedResult(const compressedResult& compressedText)
{
	trie.reset(new HuffmanTrie(nullptr));
	compressedResult::const_iterator endOfTheTrie = trie->constructFromBinaryRepresentation(compressedText);
	compressedResult text(endOfTheTrie, compressedText.end());
	return expandTextOnly(text);
}