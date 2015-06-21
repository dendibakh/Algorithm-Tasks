#include "stdafx.h"
#include "CppUnitTest.h"
#include "LZWCompression.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataCompressionTest
{
	TEST_CLASS(LZWComressionUnitTest)
	{
		class LZWCompressionFake : public LZWCompression
		{
		public:
			LZWCompressionFake() {}
			virtual ~LZWCompressionFake() {}

			using LZWCompression::trie;
			using LZWCompression::SymbolTable;
			using LZWCompression::symbTable;
			using LZWCompression::fillTrieWithRadixSymbols;
			using LZWCompression::fillSymbolTable;
		};

	public:

		template <class T>
		void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
		{
			Assert::AreEqual(lhs.size(), rhs.size());
			Assert::IsTrue(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		TEST_METHOD(LZWComressionUnitTest1)
		{
			Assert::AreEqual(1u, sizeof(char));
			Assert::AreEqual(2u, sizeof(short));

			LZWCompressionFake lzw;
			lzw.trie.reset(new LZW_TST());
			lzw.fillTrieWithRadixSymbols();

			for (unsigned int i = 0; i < LZW_TST::radix; ++i)
			{
				unsigned char c = static_cast<unsigned char>(i);
				Assert::IsTrue(lzw.trie->exist(std::string(1, c)));
				Assert::AreEqual(static_cast<short>(c), lzw.trie->getValue(std::string(1, c)));
			}
		}

		TEST_METHOD(LZWComressionUnitTest2)
		{
			LZWCompressionFake lzw;
			std::string text = "ABRACADABRABRABRA";
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			LZWCompressionFake::compressedResult expected = {65, 66, 82, 65, 67, 65, 68, 257, 259, 258, 264, 65, 256};
			checkTwoVectorsAreEqual(expected, actual);
			//float Compressionrate = (float(text.size()) / expected.size()) / 2; // 0.63
		}

		TEST_METHOD(LZWComressionUnitTest3)
		{
			LZWCompressionFake lzw;
			std::string text = "THIS IS THETHE";
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			LZWCompressionFake::compressedResult expected = { 84, 72, 73, 83, 32, 259, 32, 257, 69, 264, 256 };
			checkTwoVectorsAreEqual(expected, actual);
			//float Compressionrate = (float(text.size()) / expected.size()) / 2; // 0.63
		}

		TEST_METHOD(LZWComressionUnitTest4)
		{
			LZWCompressionFake lzw;
			std::string text = "THIS IS THETHETHETHE";
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			LZWCompressionFake::compressedResult expected = { 84, 72, 73, 83, 32, 259, 32, 257, 69, 264, 266, 72, 69, 256 };
			checkTwoVectorsAreEqual(expected, actual);
			//float Compressionrate = (float(text.size()) / expected.size()) / 2; // 0.71
		}

		TEST_METHOD(LZWComressionUnitTest5)
		{
			LZWCompressionFake lzw;
			lzw.symbTable.reset(new LZWCompressionFake::SymbolTable(LZW_TST::radix));
			lzw.fillSymbolTable();

			for (unsigned int i = 0; i < LZW_TST::radix; ++i)
			{
				unsigned char c = static_cast<unsigned char>(i);
				Assert::IsTrue((*lzw.symbTable)[c] == std::string(1, c));
			}
		}
		
		TEST_METHOD(LZWComressionUnitTest6)
		{
			LZWCompressionFake lzw;
			std::string text = "ABRACADABRABRABRA";
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			std::string expandedText = lzw.getExpandedResult(actual);
			Assert::IsTrue(expandedText == text);
		}

		TEST_METHOD(LZWComressionUnitTest7)
		{
			LZWCompressionFake lzw;
			std::string text = "!";
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			std::string expandedText = lzw.getExpandedResult(actual);
			Assert::IsTrue(expandedText == text);
		}

		TEST_METHOD(LZWComressionUnitTest8)
		{
			LZWCompressionFake lzw;
			std::string text = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			std::string expandedText = lzw.getExpandedResult(actual);
			Assert::IsTrue(expandedText == text);
		}

		TEST_METHOD(LZWComressionUnitTest9)
		{
			LZWCompressionFake lzw;
			std::string text = "This is really big text! AAAAAAAAAAA let's test huffman algorithm!!!!!!";
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			std::string expandedText = lzw.getExpandedResult(actual);
			Assert::IsTrue(expandedText == text);
		}

		TEST_METHOD(LZWComressionUnitTest10)
		{
			LZWCompressionFake lzw;
			std::string text("So, now I really know what is Huffman algorithm. It is working. Go ahead and use it!");
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			std::string expandedText = lzw.getExpandedResult(actual);
			Assert::IsTrue(expandedText == text);
		}

		TEST_METHOD(LZWComressionUnitTestTrickyCase)
		{
			LZWCompressionFake lzw;
			std::string text("ABABABA");
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			std::string expandedText = lzw.getExpandedResult(actual);
			Assert::IsTrue(expandedText == text);
		}

		TEST_METHOD(LZWComressionUnitTestTrickyCaseFromStackOverFlow)
		{
			// http://stackoverflow.com/questions/10450395/lzw-decompression-algorithm
			LZWCompressionFake lzw;
			std::string text("booop");
			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(text);
			std::string expandedText = lzw.getExpandedResult(actual);
			Assert::IsTrue(expandedText == text);
		}

		TEST_METHOD(LZWComressionUnitStressTest)
		{
			LZWCompressionFake lzw;
			std::string str("This book is intended to survey the most important computer algorithms in use today,");
			str += "and to teach fundamental techniques to the growing number of people in need of";
			str += "knowing them.It is intended for use as a textbook for a second course in computer";
			str += "science, after students have acquired basic programming skills and familiarity with computer";
			str += "systems.The book also may be useful for self - study or as a reference for people engaged in";
			str += "the development of computer systems or applications programs, since it contains implemen";
			str += "tations  of  useful  algorithms  and  detailed  information  on  performance  characteristics  and";
			str += "clients.The broad perspective taken makes the book an appropriate introduction to the field.";
			str += "the study of algorithms and data structuresis fundamental to any computer";
			str += "science curriculum, but it is not just for programmers and computer - science students.Every";
			str += "one who uses a computer wants it to run faster or to solve larger problems.The algorithms";
			str += "in this book represent a body of knowledge developed over the last 50 years that has become";
			str += "indispensable.From N - body simulation problems in physics to genetic - sequencing problems";
			str += "in molecular biology, the basic methods described here have become essential in scientific";
			str += "research; from architectural modeling systems to aircraft simulation, they have become es";
			str += "sential tools in engineering; and from database systems to internet search engines, they have";
			str += "become essential parts of modern software systems.And these are but a few examplesåas the";
			str += "scope of computer applications continues to grow, so grows the impact of the basic methods";
			str += "covered here.";
			str += "Before developing our fundamental approach to studying algorithms, we develop data";
			str += "types for stacks, queues, and other low - level abstractions that we use throughout the book.";
			str += "Then we survey fundamental algorithms for sorting, searching, graphs, and strings.The last";
			str += "chapter is an overview placing the rest of the material in the book in a larger context.";

			LZWCompressionFake::compressedResult actual = lzw.getCompressedResult(str);
			std::string expandedText = lzw.getExpandedResult(actual);
			Assert::IsTrue(expandedText == str);

			// float Compressionrate = (float(str.size()) / actual.size()) / 2; // 1.03
		}
	};
}