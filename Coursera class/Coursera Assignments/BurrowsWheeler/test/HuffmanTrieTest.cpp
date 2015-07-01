#include "gtest/gtest.h"
#include "HuffmanTrie.h"

#include <algorithm>

using namespace testing;

template <class T>
void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
{
    EXPECT_EQ(lhs.size(), rhs.size());
    EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

TEST(HuffmanTrieUnitTest, test1)
{
    HuffmanTrie::Node* node = new HuffmanTrie::Node('\n', 1);
    HuffmanTrie trie(node);
}

TEST(HuffmanTrieUnitTest, test2)
{
    HuffmanTrie::Node* node = new HuffmanTrie::Node('\n', 1);
    HuffmanTrie trie(node);
    EXPECT_EQ(1u, trie.height());
    trie.clear();
    EXPECT_EQ(0u, trie.height());
}

TEST(HuffmanTrieUnitTest, test3)
{
    HuffmanTrie::Node* node1 = new HuffmanTrie::Node('\n', 1);
    HuffmanTrie trie1(node1);
    HuffmanTrie::Node* node2 = new HuffmanTrie::Node('\t', 2);
    HuffmanTrie trie2(node2);
    EXPECT_EQ(1u, trie1.height());
    EXPECT_EQ(1u, trie2.height());
    std::auto_ptr<HuffmanTrie> trie3 = trie1.mergeWithTrie(trie2);
    EXPECT_EQ(0u, trie1.height());
    EXPECT_EQ(0u, trie2.height());
}

class HuffmanTrieFake : public HuffmanTrie
{
public:
    HuffmanTrieFake(Node* n) : HuffmanTrie(n) {}
    virtual ~HuffmanTrieFake() {}
    char getDummySymbol() const {return '\n';}
};

TEST(HuffmanTrieUnitTest, test4)
{
    HuffmanTrieFake::Node* node1 = new HuffmanTrieFake::Node('a', 1);
    HuffmanTrieFake trie1(node1);
    HuffmanTrieFake::Node* node2 = new HuffmanTrieFake::Node('b', 2);
    HuffmanTrieFake trie2(node2);
    
    std::auto_ptr<HuffmanTrie> trie3 = trie1.mergeWithTrie(trie2);
    
    std::string leftTraversal = trie3->getLeftTraversal();
    std::string etalon("\n(3) \na(1) b(2) \n");
    EXPECT_TRUE(leftTraversal == etalon);
}

TEST(HuffmanTrieUnitTest, test5)
{
    HuffmanTrieFake::Node* node1 = new HuffmanTrieFake::Node('a', 1);
    HuffmanTrieFake trie1(node1);
    HuffmanTrieFake::Node* node2 = new HuffmanTrieFake::Node('b', 2);
    HuffmanTrieFake trie2(node2);

    std::auto_ptr<HuffmanTrie> trie3 = trie1.mergeWithTrie(trie2);

    std::string leftTraversal = trie3->getLeftTraversal();
    std::string etalon("\n(3) \na(1) b(2) \n");
    EXPECT_TRUE(leftTraversal == etalon);
}

TEST(HuffmanTrieUnitTest, test6)
{
    HuffmanTrieFake huffman(0);

    bool binaryRepresentationArray[] = { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                                         0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0 }; //"THIS IS "
    HuffmanTrieFake::compressedResult binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + 
                                                           sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));

    HuffmanTrieFake::compressedResult::const_iterator endOfTheTrie = huffman.constructFromBinaryRepresentation(binaryRepresentation);
    std::string actual = huffman.getLeftTraversal();
    std::string etalon("\n(0) \n\n(0) \n(0) \nI(0)  (0) S(0) \n(0) \nH(0) T(0) \n");
    EXPECT_TRUE(actual == etalon);
    EXPECT_TRUE(endOfTheTrie == binaryRepresentation.end());
}


TEST(HuffmanTrieUnitTest, test7)
{
    HuffmanTrieFake huffman(0);

    bool binaryRepresentationArray[] = { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                                         0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1 }; //"THIS IS " and 3 excessive bits
    HuffmanTrieFake::compressedResult binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + 
                                                           sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));

    HuffmanTrieFake::compressedResult::const_iterator endOfTheTrie = huffman.constructFromBinaryRepresentation(binaryRepresentation);
    std::string actual = huffman.getLeftTraversal();
    std::string etalon("\n(0) \n\n(0) \n(0) \nI(0)  (0) S(0) \n(0) \nH(0) T(0) \n");
    EXPECT_TRUE(actual == etalon);
    EXPECT_TRUE(endOfTheTrie == binaryRepresentation.end() - 3);
}

TEST(HuffmanTrieUnitTest, test8)
{
    HuffmanTrieFake huffman(0);

    bool binaryRepresentationArray[] = { 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1 }; //"ABC"
    HuffmanTrieFake::compressedResult binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + 
                                                           sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));

    HuffmanTrieFake::compressedResult::const_iterator endOfTheTrie = huffman.constructFromBinaryRepresentation(binaryRepresentation);
    std::string actual = huffman.getLeftTraversal();
    std::string etalon("\n(0) \nA(0) \n(0) \nB(0) C(0) \n");
    EXPECT_TRUE(actual == etalon);
    EXPECT_TRUE(endOfTheTrie == binaryRepresentation.end());
}
