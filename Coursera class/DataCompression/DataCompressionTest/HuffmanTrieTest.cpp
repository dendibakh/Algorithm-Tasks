#include "stdafx.h"
#include "CppUnitTest.h"
#include "HuffmanTrie.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataCompressionTest
{
	TEST_CLASS(HuffmanTrieUnitTest)
	{
	public:

		template <class T>
		void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
		{
			Assert::AreEqual(lhs.size(), rhs.size());
			Assert::IsTrue(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		TEST_METHOD(HuffmanTrieUnitTest1)
		{
			HuffmanTrie::Node* node = new HuffmanTrie::Node('\n', 1);
			HuffmanTrie trie(node);
		}

		TEST_METHOD(HuffmanTrieUnitTest2)
		{
			HuffmanTrie::Node* node = new HuffmanTrie::Node('\n', 1);
			HuffmanTrie trie(node);
			Assert::AreEqual(1u, trie.height());
			trie.clear();
			Assert::AreEqual(0u, trie.height());
		}
		
		TEST_METHOD(HuffmanTrieUnitTest3)
		{
			HuffmanTrie::Node* node1 = new HuffmanTrie::Node('\n', 1);
			HuffmanTrie trie1(node1);
			HuffmanTrie::Node* node2 = new HuffmanTrie::Node('\t', 2);
			HuffmanTrie trie2(node2);
			Assert::AreEqual(1u, trie1.height());
			Assert::AreEqual(1u, trie2.height());
			std::unique_ptr<HuffmanTrie> trie3 = trie1.mergeWithTrie(trie2);
			Assert::AreEqual(0u, trie1.height());
			Assert::AreEqual(0u, trie2.height());
		}

		class HuffmanTrieFake : public HuffmanTrie
		{
		public:
			HuffmanTrieFake(Node* n) : HuffmanTrie(n) {}
			virtual ~HuffmanTrieFake() {}
			char getDummySymbol() const {return '\n';}
		};

		TEST_METHOD(HuffmanTrieUnitTest4)
		{
			HuffmanTrieFake::Node* node1 = new HuffmanTrieFake::Node('a', 1);
			HuffmanTrieFake trie1(node1);
			HuffmanTrieFake::Node* node2 = new HuffmanTrieFake::Node('b', 2);
			HuffmanTrieFake trie2(node2);
			
			std::unique_ptr<HuffmanTrie> trie3 = trie1.mergeWithTrie(trie2);
			
			std::string leftTraversal = trie3->getLeftTraversal();
			std::string etalon("\n(3) \na(1) b(2) \n");
			Assert::IsTrue(leftTraversal == etalon);
		}

		TEST_METHOD(HuffmanTrieUnitTest5)
		{
			HuffmanTrieFake::Node* node1 = new HuffmanTrieFake::Node('a', 1);
			HuffmanTrieFake trie1(node1);
			HuffmanTrieFake::Node* node2 = new HuffmanTrieFake::Node('b', 2);
			HuffmanTrieFake trie2(node2);

			std::unique_ptr<HuffmanTrie> trie3 = trie1.mergeWithTrie(trie2);

			std::string leftTraversal = trie3->getLeftTraversal();
			std::string etalon("\n(3) \na(1) b(2) \n");
			Assert::IsTrue(leftTraversal == etalon);
		}

		TEST_METHOD(HuffmanTrieUnitTest6)
		{
			HuffmanTrieFake huffman(nullptr);
		
			HuffmanTrieFake::compressedResult binaryRepresentation = { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
				0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0 }; //"THIS IS "

			HuffmanTrieFake::compressedResult::const_iterator endOfTheTrie = huffman.constructFromBinaryRepresentation(binaryRepresentation);
			std::string actual = huffman.getLeftTraversal();
			std::string etalon("\n(0) \n\n(0) \n(0) \nI(0)  (0) S(0) \n(0) \nH(0) T(0) \n");
			Assert::IsTrue(actual == etalon);
			Assert::IsTrue(endOfTheTrie == binaryRepresentation.end());
		}


		TEST_METHOD(HuffmanTrieUnitTest7)
		{
			HuffmanTrieFake huffman(nullptr);

			HuffmanTrieFake::compressedResult binaryRepresentation = { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
				0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1 }; //"THIS IS " and 3 excessive bits

			HuffmanTrieFake::compressedResult::const_iterator endOfTheTrie = huffman.constructFromBinaryRepresentation(binaryRepresentation);
			std::string actual = huffman.getLeftTraversal();
			std::string etalon("\n(0) \n\n(0) \n(0) \nI(0)  (0) S(0) \n(0) \nH(0) T(0) \n");
			Assert::IsTrue(actual == etalon);
			Assert::IsTrue(endOfTheTrie == binaryRepresentation.end() - 3);
		}

		TEST_METHOD(HuffmanTrieUnitTest8)
		{
			HuffmanTrieFake huffman(nullptr);

			HuffmanTrieFake::compressedResult binaryRepresentation = { 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1 }; //"ABC"

			HuffmanTrieFake::compressedResult::const_iterator endOfTheTrie = huffman.constructFromBinaryRepresentation(binaryRepresentation);
			std::string actual = huffman.getLeftTraversal();
			std::string etalon("\n(0) \nA(0) \n(0) \nB(0) C(0) \n");
			Assert::IsTrue(actual == etalon);
			Assert::IsTrue(endOfTheTrie == binaryRepresentation.end());
		}
	};
}