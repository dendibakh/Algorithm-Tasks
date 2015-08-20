#include "gtest/gtest.h"
#include "HuffmanCompression.h"

#include <algorithm>

using namespace testing;

template <class T>
void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
{
    EXPECT_EQ(lhs.size(), rhs.size());
    EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T>
void checkTwoMatrixAreEqual(const T& lhs, const T& rhs)
{
    EXPECT_EQ(lhs.size(), rhs.size());
    for (size_t i = 0; i < lhs.size(); ++i)
    {
        checkTwoVectorsAreEqual(lhs[i], rhs[i]);
    }
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

TEST(HuffmanAlgorithmUnitTest, test1)
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

TEST(HuffmanAlgorithmUnitTest, test2)
{
    HuffmanAlgorithmFake huffman;
    huffman.buildTrie("THIS IS ");
    
    std::string leftTraversal = huffman.trie->getLeftTraversal();
    std::string etalon("\n(8) \n\n(4) \n(4) \nI(2)  (2) S(2) \n(2) \nH(1) T(1) \n");
    EXPECT_TRUE(leftTraversal == etalon);
}

TEST(HuffmanAlgorithmUnitTest, test3)
{
    HuffmanAlgorithmFake huffman;
    huffman.buildTrie("THIS IS ");

    HuffmanAlgorithmFake::HuffmanTrieFake::SymbolTable sbTable = huffman.trie->getSymbolTable();
    HuffmanAlgorithmFake::HuffmanTrieFake::SymbolTable expected(HuffmanAlgorithmFake::HuffmanTrieFake::radix);
    bool expectedI[] = { 0, 0 };     expected['I'] = std::vector<bool>(expectedI, expectedI + sizeof(expectedI) / sizeof (expectedI[0]));
    bool expectedSPACE[] = { 0, 1 }; expected[' '] = std::vector<bool>(expectedSPACE, expectedSPACE + sizeof(expectedSPACE) / sizeof (expectedSPACE[0]));
    bool expectedS[] = { 1, 0 };     expected['S'] = std::vector<bool>(expectedS, expectedS + sizeof(expectedS) / sizeof (expectedS[0]));
    bool expectedH[] = { 1, 1, 0 };  expected['H'] = std::vector<bool>(expectedH, expectedH + sizeof(expectedH) / sizeof (expectedH[0]));
    bool expectedT[] = { 1, 1, 1 };  expected['T'] = std::vector<bool>(expectedT, expectedT + sizeof(expectedT) / sizeof (expectedT[0]));
    checkTwoMatrixAreEqual(sbTable, expected);
}

TEST(HuffmanAlgorithmUnitTest, test4)
{
    HuffmanAlgorithmFake huffman;
    huffman.buildTrie("ABRACADABRA!");

    HuffmanAlgorithmFake::HuffmanTrieFake::SymbolTable sbTable = huffman.trie->getSymbolTable();
    HuffmanAlgorithmFake::HuffmanTrieFake::SymbolTable expected(HuffmanAlgorithmFake::HuffmanTrieFake::radix);
    bool expectedSign[] = { 1, 1, 0, 0 }; expected['!'] = std::vector<bool>(expectedSign, expectedSign + sizeof(expectedSign) / sizeof (expectedSign[0]));
    bool expectedA[] = { 0 };             expected['A'] = std::vector<bool>(expectedA, expectedA + sizeof(expectedA) / sizeof (expectedA[0]));
    bool expectedB[] = { 1, 0, 1 };       expected['B'] = std::vector<bool>(expectedB, expectedB + sizeof(expectedB) / sizeof (expectedB[0]));
    bool expectedC[] = { 1, 1, 0, 1 };    expected['C'] = std::vector<bool>(expectedC, expectedC + sizeof(expectedC) / sizeof (expectedC[0]));
    bool expectedD[] = { 1, 0, 0 };       expected['D'] = std::vector<bool>(expectedD, expectedD + sizeof(expectedD) / sizeof (expectedD[0]));
    bool expectedR[] = { 1, 1, 1 };       expected['R'] = std::vector<bool>(expectedR, expectedR + sizeof(expectedR) / sizeof (expectedR[0]));
    checkTwoMatrixAreEqual(sbTable, expected);
}

TEST(HuffmanAlgorithmUnitTest, test5)
{
    bool expectedArray[] = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 };
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult expected(expectedArray, expectedArray + sizeof(expectedArray) / sizeof (expectedArray[0]));
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult actual = HuffmanAlgorithmFake().compressTextOnly("THIS IS ");
    checkTwoVectorsAreEqual(expected, actual);
    // Compressionrate: 8 * 8 = 64 bit -> 18 bit. (3,55)
}

TEST(HuffmanAlgorithmUnitTest, test6)
{
    bool expectedArray[] = { 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0};
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult expected(expectedArray, expectedArray + sizeof(expectedArray) / sizeof (expectedArray[0]));
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult actual = HuffmanAlgorithmFake().compressTextOnly("ABRACADABRA!");
    checkTwoVectorsAreEqual(expected, actual);
    // Compressionrate: 12 * 8 = 96 bit -> 28 bit. (3,42)
}

TEST(HuffmanAlgorithmUnitTest, test7)
{
    std::string text = "THIS IS ";
    HuffmanAlgorithmFake huffman;
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
    std::string decompressedText = huffman.expandTextOnly(comressedText);
    EXPECT_TRUE(text == decompressedText);
}

TEST(HuffmanAlgorithmUnitTest, test8)
{
    std::string text = "ABRACADABRA!";
    HuffmanAlgorithmFake huffman;
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
    std::string decompressedText = huffman.expandTextOnly(comressedText);
    EXPECT_TRUE(text == decompressedText);
}

TEST(HuffmanAlgorithmUnitTest, test9)
{
    std::string text = "!";
    HuffmanAlgorithmFake huffman;
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
    std::string decompressedText = huffman.expandTextOnly(comressedText);
    EXPECT_TRUE(text == decompressedText);
}

TEST(HuffmanAlgorithmUnitTest, test10)
{
    std::string text = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    HuffmanAlgorithmFake huffman;
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
    std::string decompressedText = huffman.expandTextOnly(comressedText);
    EXPECT_TRUE(text == decompressedText);
}

TEST(HuffmanAlgorithmUnitTest, test11)
{
    std::string text = "This is really big text! AAAAAAAAAAA let's test huffman algorithm!!!!!!";
    HuffmanAlgorithmFake huffman;
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult comressedText = huffman.compressTextOnly(text);
    std::string decompressedText = huffman.expandTextOnly(comressedText);
    EXPECT_TRUE(text == decompressedText);
}

TEST(HuffmanAlgorithmUnitTest, test12)
{
    HuffmanAlgorithmFake huffman;
    huffman.buildTrie("THIS IS ");

    bool expectedArray[] = { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0 };
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult expected(expectedArray, expectedArray + sizeof(expectedArray) / sizeof (expectedArray[0]));
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult actualtrieBinary = huffman.trie->serializeTrie();
    checkTwoVectorsAreEqual(expected, actualtrieBinary);
}

TEST(HuffmanAlgorithmUnitTest, test13)
{
    HuffmanAlgorithmFake huffman;
    huffman.buildTrie("ABRACADABRA!");

    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult actualtrieBinary = huffman.trie->serializeTrie();
    bool expectedArray[] = { 
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
    	0, 1, 0, 1, 0, 0, 1, 0 };
    HuffmanAlgorithmFake::HuffmanTrieFake::compressedResult expected(expectedArray, expectedArray + sizeof(expectedArray) / sizeof (expectedArray[0]));
    checkTwoVectorsAreEqual(expected, actualtrieBinary);
}

TEST(HuffmanAlgorithmUnitTest, test14)
{
    HuffmanAlgorithmFake huffman;
    std::string text("ABRACADABRA!");
    HuffmanAlgorithmFake::compressedResult compressed = huffman.getCompressedResult(text);
    std::string expanded = huffman.getExpandedResult(compressed);
    EXPECT_TRUE(text == expanded);
}

TEST(HuffmanAlgorithmUnitTest, test15)
{
    HuffmanAlgorithmFake huffman;
    std::string text("So, now I really know what is Huffman algorithm. It is working. Go ahead and use it!");
    HuffmanAlgorithmFake::compressedResult compressed = huffman.getCompressedResult(text);
    std::string expanded = huffman.getExpandedResult(compressed);
    EXPECT_TRUE(text == expanded);
}

TEST(HuffmanAlgorithmUnitTest, test16)
{
    std::string str("This book is intended to survey the most important computer algorithms in use today,\n");
        str += "and to teach fundamental techniques to the growing number of people in need of\n";
        str += "knowing them.It is intended for use as a textbook for a second course in computer\n";
        str += "science, after students have acquired basic programming skills and familiarity with computer\n";
        str += "systems.The book also may be useful for self - study or as a reference for people engaged in\n";
        str += "the development of computer systems or applications programs, since it contains implemen\n";
        str += "tations  of  useful  algorithms  and  detailed  information  on  performance  characteristics and\n";
        str += "clients.The broad perspective taken makes the book an appropriate introduction to the field.\n";
        str += "the study of algorithms and data structuresis fundamental to any computer\n";
        str += "science curriculum, but it is not just for programmers and computer - science students.Every\n";
        str += "one who uses a computer wants it to run faster or to solve larger problems.The algorithms\n";
        str += "in this book represent a body of knowledge developed over the last fifty years that has become\n";
        str += "indispensable.From N - body simulation problems in physics to genetic - sequencing problems\n";
        str += "in molecular biology, the basic methods described here have become essential in scientific\n";
        str += "research; from architectural modeling systems to aircraft simulation, they have become es\n";
        str += "sential tools in engineering; and from database systems to internet search engines, they have\n";
        str += "become essential parts of modern software systems.And these are but a few examples as the\n";
        str += "scope of computer applications continues to grow, so grows the impact of the basic methods\n";
        str += "covered here.\n";
        str += "Before developing our fundamental approach to studying algorithms, we develop data\n";
        str += "types for stacks, queues, and other low - level abstractions that we use throughout the book.\n";
        str += "Then we survey fundamental algorithms for sorting, searching, graphs, and strings.The last\n";
        str += "chapter is an overview placing the rest of the material in the book in a larger context.\n";

    HuffmanAlgorithmFake huffman;
    HuffmanAlgorithmFake::compressedResult compressed = huffman.getCompressedResult(str);
    std::string expanded = huffman.getExpandedResult(compressed);
    EXPECT_TRUE(str == expanded);
    /*
    #include <iostream>
    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size();
    std::cout << "originalSize = " << originalSize << std::endl;
    std::cout << "compressedSize = " << compressedSize << std::endl;
    std::cout << "Comression rate = " << (float)originalSize / compressedSize << std::endl;
    */
    // For this case Comression rate = 1.766.
}
