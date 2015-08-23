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

/*
[----------] 3 tests from BenchMarkTest1
[ RUN      ] BenchMarkTest1.LZW
originalSize = 1875024
compressedSize = 1555936
Comression rate = 1.20508
[       OK ] BenchMarkTest1.LZW (229 ms)
[ RUN      ] BenchMarkTest1.Huffman
originalSize = 1875024
compressedSize = 1086340
Comression rate = 1.726
[       OK ] BenchMarkTest1.Huffman (360 ms)
[ RUN      ] BenchMarkTest1.BurrowsWheeler
originalSize = 1875024
compressedSize = 561334
Comression rate = 3.3403
[       OK ] BenchMarkTest1.BurrowsWheeler (971 ms)
*/

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

// Comression rates for the example for BenchMarkTest2:
// - Huffman - 1.7845.
// - BurrowsWheeler - 2.878.
// - LZW - 1.303

/*
[----------] 3 tests from BenchMarkTest2
[ RUN      ] BenchMarkTest2.LZW
originalSize = 9531704
compressedSize = 7315808
Comression rate = 1.30289
[       OK ] BenchMarkTest2.LZW (1203 ms)
[ RUN      ] BenchMarkTest2.BurrowsWheeler
originalSize = 9531704
compressedSize = 3311668
Comression rate = 2.87822
[       OK ] BenchMarkTest2.BurrowsWheeler (5418 ms)
[ RUN      ] BenchMarkTest2.Huffman
originalSize = 9531704
compressedSize = 5341176
Comression rate = 1.78457
[       OK ] BenchMarkTest2.Huffman (1694 ms)
*/


TEST(BenchMarkTest3, LZW)
{
    std::string str(readFile("./test/samples/bible.txt"));

    LZWCompression obj;
    LZWCompression::compressedResult compressed = obj.getCompressedResult(str);
    std::string decoded = obj.getExpandedResult(compressed);
    EXPECT_TRUE(str == decoded);

    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size() * sizeof(unsigned int) * 8;
    printCompressionRate(originalSize, compressedSize);
    
    // For this case Comression rate = 1.843. It is because we are using 4 bytes as an ID for symbolTable.
}

TEST(BenchMarkTest3, Huffman)
{
    std::string str(readFile("./test/samples/bible.txt"));

    HuffmanAlgorithm huffman;
    HuffmanAlgorithm::compressedResult compressed = huffman.getCompressedResult(str);
    std::string expanded = huffman.getExpandedResult(compressed);
    EXPECT_TRUE(str == expanded);

    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size();
    printCompressionRate(originalSize, compressedSize);

    // For this case Comression rate = 1.824.
}

TEST(BenchMarkTest3, BurrowsWheeler)
{
    std::string str(readFile("./test/samples/bible.txt"));

    BurrowsWheeler obj;
    BurrowsWheeler::compressedResult compressed = obj.encode(str);
    std::string decoded = obj.decode(compressed);
    EXPECT_TRUE(str == decoded);
    
    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size();
    printCompressionRate(originalSize, compressedSize);

    // For this case Comression rate = 3.838.
}

/*
[----------] 3 tests from BenchMarkTest3
[ RUN      ] BenchMarkTest3.LZW
originalSize = 32379136
compressedSize = 17568416
Comression rate = 1.84303
[       OK ] BenchMarkTest3.LZW (3224 ms)
[ RUN      ] BenchMarkTest3.Huffman
originalSize = 32379136
compressedSize = 17748224
Comression rate = 1.82436
[       OK ] BenchMarkTest3.Huffman (5903 ms)
[ RUN      ] BenchMarkTest3.BurrowsWheeler
originalSize = 32379136
compressedSize = 8434677
Comression rate = 3.83881
[       OK ] BenchMarkTest3.BurrowsWheeler (19545 ms)
*/
