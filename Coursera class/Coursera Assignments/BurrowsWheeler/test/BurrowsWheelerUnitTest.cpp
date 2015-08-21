#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "BurrowsWheeler.h"
#include "utils.h"

using namespace testing;

#include <iostream>

#define UNUSED_VARIABLE(x) (void)x

class BurrowsWheelerTest : public ::testing::Test 
{
protected:
    BurrowsWheelerTest() { }
    virtual ~BurrowsWheelerTest() { }
    virtual void SetUp() { }
    virtual void TearDown() { }

    class BurrowsWheelerFake : public BurrowsWheeler
    {
    };
};

TEST_F(BurrowsWheelerTest, test_constructor)
{
    BurrowsWheelerFake obj;
    UNUSED_VARIABLE(obj);
}

TEST_F(BurrowsWheelerTest, combinedTest1)
{
    std::string text("ABRACADABRA!");
    BurrowsWheelerFake obj;
    BurrowsWheeler::compressedResult compressed = obj.encode(text);
    std::string decoded = obj.decode(compressed);
    EXPECT_TRUE(text == decoded);
}

TEST_F(BurrowsWheelerTest, combinedTest2)
{
    std::string text("So, now I really know what is BurrowsWheeler algorithm. It is working. Go ahead and use it!");
    BurrowsWheelerFake obj;
    BurrowsWheeler::compressedResult compressed = obj.encode(text);
    std::string decoded = obj.decode(compressed);
    EXPECT_TRUE(text == decoded);
}

TEST_F(BurrowsWheelerTest, combinedTest3)
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

    BurrowsWheelerFake obj;
    BurrowsWheeler::compressedResult compressed = obj.encode(str);
    std::string decoded = obj.decode(compressed);
    EXPECT_TRUE(str == decoded);
    /*
    #include <iostream>
    size_t originalSize = str.size() * 8;
    size_t compressedSize = compressed.size();
    std::cout << "originalSize = " << originalSize << std::endl;
    std::cout << "compressedSize = " << compressedSize << std::endl;
    std::cout << "Comression rate = " << (float)originalSize / compressedSize << std::endl;
    */
    // For this case Comression rate = 1.99296.
}

// Comression rates for the example from TEST_F(BurrowsWheelerTest, combinedTest3):
// - Huffman - 1.766.
// - BurrowsWheeler - 1.99296.
// - LZW - 1.03
