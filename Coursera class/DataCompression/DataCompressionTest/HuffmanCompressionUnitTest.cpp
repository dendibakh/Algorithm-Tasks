#include "stdafx.h"
#include "CppUnitTest.h"
#include "HuffmanCompression.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataCompressionTest
{
	TEST_CLASS(HuffmanAlgorithmUnitTest)
	{
	public:

		template <class T>
		void checkTwoMatrixAreEqual(const T& lhs, const T& rhs)
		{
			Assert::AreEqual(lhs.size(), rhs.size());
			for (size_t i = 0; i < lhs.size(); ++i)
			{
				checkTwoVectorsAreEqual(lhs[i], rhs[i]);
			}
		}

		template <class T>
		void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
		{
			Assert::AreEqual(lhs.size(), rhs.size());
			Assert::IsTrue(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		class HuffmanAlgorithmFake : public HuffmanAlgorithm
		{
		public:
			using HuffmanAlgorithm::countFrequencies;
			using HuffmanAlgorithm::buildTrie;
			using HuffmanAlgorithm::compressTextOnly;
			using HuffmanAlgorithm::expandTextOnly;
			using HuffmanAlgorithm::freq;
			using HuffmanAlgorithm::trie;

			class HuffmanTrieFake : public HuffmanTrie
			{
			public:
				HuffmanTrieFake(Node* n) : HuffmanTrie(n) {}
				virtual ~HuffmanTrieFake() {}
				virtual HuffmanTrie* createNewTrie(HuffmanTrie::Node* node) const
				{
					return new HuffmanTrieFake(node);
				}
				char getDummySymbol() const { return '\n'; }
			};
		private:
			virtual HuffmanTrie* createNewTrie(HuffmanTrie::Node* node) const
			{
				return new HuffmanTrieFake(node);
			}
		};

		TEST_METHOD(HuffmanAlgorithmUnitTest1)
		{
			HuffmanAlgorithmFake huffman;
			huffman.countFrequencies("THIS IS HUFFMAN ALGORITHM");
			std::vector<size_t> expected(HuffmanAlgorithmFake::HuffmanTrieFake::radix, 0);
			expected[32] = 3;
			expected[65] = 2;
			expected[70] = 2;
			expected[71] = 1;
			expected[72] = 3;
			expected[73] = 3;
			expected[76] = 1;
			expected[77] = 2;
			expected[78] = 1;
			expected[79] = 1;
			expected[82] = 1;
			expected[83] = 2;
			expected[84] = 2;
			expected[85] = 1;
			checkTwoVectorsAreEqual(expected, huffman.freq);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest2)
		{
			HuffmanAlgorithmFake huffman;
			huffman.buildTrie("THIS IS ");
			
			std::string leftTraversal = huffman.trie->getLeftTraversal();
			std::string etalon("\n(8) \n\n(4) \n(4) \nI(2)  (2) S(2) \n(2) \nH(1) T(1) \n");
			Assert::IsTrue(leftTraversal == etalon);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest3)
		{
			HuffmanAlgorithmFake huffman;
			huffman.buildTrie("THIS IS ");

			HuffmanAlgorithmFake::HuffmanTrieFake::SymbolTable sbTable = huffman.trie->getSymbolTable();
			HuffmanAlgorithmFake::HuffmanTrieFake::SymbolTable expected(HuffmanAlgorithmFake::HuffmanTrieFake::radix);
			expected['I'] = { 0, 0 };
			expected[' '] = { 0, 1 };
			expected['S'] = { 1, 0 };
			expected['H'] = { 1, 1, 0 };
			expected['T'] = { 1, 1, 1 };
			checkTwoMatrixAreEqual(sbTable, expected);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest4)
		{
			HuffmanAlgorithmFake huffman;
			huffman.buildTrie("ABRACADABRA!");

			HuffmanAlgorithmFake::HuffmanTrieFake::SymbolTable sbTable = huffman.trie->getSymbolTable();
			HuffmanAlgorithmFake::HuffmanTrieFake::SymbolTable expected(HuffmanAlgorithmFake::HuffmanTrieFake::radix);
			expected['!'] = { 1, 1, 0, 0 };
			expected['A'] = { 0 };
			expected['B'] = { 1, 0, 1 };
			expected['C'] = { 1, 1, 0, 1 };
			expected['D'] = { 1, 0, 0 };
			expected['R'] = { 1, 1, 1 };
			checkTwoMatrixAreEqual(sbTable, expected);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest5)
		{
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult expected = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 };
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult actual = HuffmanAlgorithmFake().compressTextOnly("THIS IS ");
			checkTwoVectorsAreEqual(expected, actual);
			// Compressionrate: 8 * 8 = 64 bit -> 18 bit. (3,55)
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest6)
		{
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult expected = { 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0};
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult actual = HuffmanAlgorithmFake().compressTextOnly("ABRACADABRA!");
			checkTwoVectorsAreEqual(expected, actual);
			// Compressionrate: 12 * 8 = 96 bit -> 28 bit. (3,42)
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest7)
		{
			std::string text = "THIS IS ";
			HuffmanAlgorithmFake huffman;
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
			std::string decompressedText = huffman.expandTextOnly(comressedText);
			Assert::IsTrue(text == decompressedText);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest8)
		{
			std::string text = "ABRACADABRA!";
			HuffmanAlgorithmFake huffman;
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
			std::string decompressedText = huffman.expandTextOnly(comressedText);
			Assert::IsTrue(text == decompressedText);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest9)
		{
			std::string text = "!";
			HuffmanAlgorithmFake huffman;
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
			std::string decompressedText = huffman.expandTextOnly(comressedText);
			Assert::IsTrue(text == decompressedText);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest10)
		{
			std::string text = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
			HuffmanAlgorithmFake huffman;
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
			std::string decompressedText = huffman.expandTextOnly(comressedText);
			Assert::IsTrue(text == decompressedText);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest11)
		{
			std::string text = "This is really big text! AAAAAAAAAAA let's test huffman algorithm!!!!!!";
			HuffmanAlgorithmFake huffman;
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
			std::string decompressedText = huffman.expandTextOnly(comressedText);
			Assert::IsTrue(text == decompressedText);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest12)
		{
			HuffmanAlgorithmFake huffman;
			huffman.buildTrie("THIS IS ");

			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult actualtrieBinary = huffman.trie->serializeTrie();
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult expected = { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
				0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0 };
			checkTwoVectorsAreEqual(expected, actualtrieBinary);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest13)
		{
			HuffmanAlgorithmFake huffman;
			huffman.buildTrie("ABRACADABRA!");

			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult actualtrieBinary = huffman.trie->serializeTrie();
			HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult expected = { 
				0, 
				1, 
				0, 1, 0, 0, 0, 0, 0, 1, 
				0, 0,
				1,
				0, 1, 0, 0, 0, 1, 0, 0, 
				1,
				0, 1, 0, 0, 0, 0, 1, 0, 
				0, 0, 
				1,
				0, 0, 1, 0, 0, 0, 0, 1, 
				1,
				0, 1, 0, 0, 0, 0, 1, 1,
				1, 
				0, 1, 0, 1, 0, 0, 1, 0};
			checkTwoVectorsAreEqual(expected, actualtrieBinary);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest14)
		{
			HuffmanAlgorithmFake huffman;
			std::string text("ABRACADABRA!");
			HuffmanAlgorithmFake::compressedResult compressed = huffman.getCompressedResult(text);
			std::string expanded = huffman.getExpandedResult(compressed);
			Assert::IsTrue(text == expanded);
		}

		TEST_METHOD(HuffmanAlgorithmUnitTest15)
		{
			HuffmanAlgorithmFake huffman;
			std::string text("So, now I really know what is Huffman algorithm. It is working. Go ahead and use it!");
			HuffmanAlgorithmFake::compressedResult compressed = huffman.getCompressedResult(text);
			std::string expanded = huffman.getExpandedResult(compressed);
			Assert::IsTrue(text == expanded);
		}
	};
}