#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "LZWCompression.h"
#include "BurrowsWheeler.h"
#include "utils.h"

#include <iostream>

using namespace testing;

namespace
{
    void printCompressionRate(size_t originalSize, size_t compressedSize)
    {
        std::cout << "originalSize = " << originalSize << std::endl;
        std::cout << "compressedSize = " << compressedSize << std::endl;
        std::cout << "Comression rate = " << (float)originalSize / compressedSize << std::endl;
    }
}

TEST(BenchMarkTest1, LZW)
{
    std::string str(readFile("./test/samples/starr.txt"));

    LZWCompression obj;
    LZWCompression::compressedResult compressed = obj.getCompressedResult(str);
    std::string decoded = obj.getExpandedResult(compressed);
    EXPECT_TRUE(str == decoded);

    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size() * sizeof(unsigned int) * 8;
    printCompressionRate(originalSize, compressedSize);
    
    // For this case Comression rate = 1.20508. It is because we are using 4 bytes as an ID for symbolTable.
}

TEST(BenchMarkTest1, Huffman)
{
    std::string str(readFile("./test/samples/starr.txt"));

    HuffmanAlgorithm huffman;
    HuffmanAlgorithm::compressedResult compressed = huffman.getCompressedResult(str);
    std::string expanded = huffman.getExpandedResult(compressed);
    EXPECT_TRUE(str == expanded);

    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size();
    printCompressionRate(originalSize, compressedSize);

    // For this case Comression rate = 1.726.
}

TEST(BenchMarkTest1, BurrowsWheeler)
{
    std::string str(readFile("./test/samples/starr.txt"));

    BurrowsWheeler obj;
    BurrowsWheeler::compressedResult compressed = obj.encode(str);
    std::string decoded = obj.decode(compressed);
    EXPECT_TRUE(str == decoded);
    
    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size();
    printCompressionRate(originalSize, compressedSize);

    // For this case Comression rate = 3.3403.
}

// Comression rates for the example for BenchMarkTest1:
// - Huffman - 1.726.
// - BurrowsWheeler - 3.3403.
// - LZW - 1.20508

TEST(BenchMarkTest2, LZW)
{
    std::string str(readFile("./test/samples/mobydick.txt"));

    LZWCompression obj;
    LZWCompression::compressedResult compressed = obj.getCompressedResult(str);
    std::string decoded = obj.getExpandedResult(compressed);
    EXPECT_TRUE(str == decoded);

    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size() * sizeof(unsigned int) * 8;
    printCompressionRate(originalSize, compressedSize);
    
    // For this case Comression rate = 1.303. It is because we are using 4 bytes as an ID for symbolTable.
}

TEST(BenchMarkTest2, BurrowsWheeler)
{
    std::string str(readFile("./test/samples/mobydick.txt"));

    BurrowsWheeler obj;
    BurrowsWheeler::compressedResult compressed = obj.encode(str);
    std::string decoded = obj.decode(compressed);
    EXPECT_TRUE(str == decoded);
    
    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size();
    printCompressionRate(originalSize, compressedSize);

    // For this case Comression rate = 2.878.
}

TEST(BenchMarkTest2, Huffman)
{
    std::string str(readFile("./test/samples/mobydick.txt"));

    HuffmanAlgorithm huffman;
    HuffmanAlgorithm::compressedResult compressed = huffman.getCompressedResult(str);
    std::string expanded = huffman.getExpandedResult(compressed);
    EXPECT_TRUE(str == expanded);

    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size();
    printCompressionRate(originalSize, compressedSize);

    // For this case Comression rate = 1.7845.
}

// Comression rates for the example for BenchMarkTest2:
// - Huffman - 1.7845.
// - BurrowsWheeler - 2.878.
// - LZW - 1.303
