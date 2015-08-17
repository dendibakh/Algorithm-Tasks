#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "BurrowsWheelerTransform.h"

#include <iostream>

using namespace testing;

TEST(BurrowsWheelerTransformTest, test1)
{
    std::string str = "ABRACADABRA!";
    BurrowsWheelerTransform BWTransform(str);
    
    EXPECT_EQ(3u, BWTransform.getOriginalStringRow());
    std::string etalonTransformed = "ARD!RCAAAABB";
    EXPECT_TRUE(etalonTransformed == BWTransform.getTransformedStr());
}

TEST(BurrowsWheelerTransformTest, test2)
{
    std::string str = "ABRA!";
    BurrowsWheelerTransform BWTransform(str);
    
    EXPECT_EQ(2u, BWTransform.getOriginalStringRow());
    std::string etalonTransformed = "AR!AB";
    EXPECT_TRUE(etalonTransformed == BWTransform.getTransformedStr());
}

class BurrowsWheelerDecodeFake : public BurrowsWheelerDecode
{
public:
    BurrowsWheelerDecodeFake(size_t originalStringRow, const std::string& str) : BurrowsWheelerDecode(originalStringRow, str) {}
    using BurrowsWheelerDecode::sortedStr;
};

TEST(BurrowsWheelerTransformTest, test3_decode)
{
    std::string str = "ABRA!";
    BurrowsWheelerTransform BWTransform(str);
    BurrowsWheelerDecode BWDecode(BWTransform.getOriginalStringRow(), BWTransform.getTransformedStr());
    EXPECT_TRUE(str == BWDecode.getOriginalString());
}

TEST(BurrowsWheelerTransformTest, test3_checkNext)
{
    std::string str = "ABRA!";
    BurrowsWheelerTransform BWTransform(str);
    BurrowsWheelerDecodeFake BWDecode(BWTransform.getOriginalStringRow(), BWTransform.getTransformedStr());
    EXPECT_EQ(2u, BWDecode.sortedStr[0].second);
    EXPECT_EQ(0u, BWDecode.sortedStr[1].second);
    EXPECT_EQ(3u, BWDecode.sortedStr[2].second);
    EXPECT_EQ(4u, BWDecode.sortedStr[3].second);
    EXPECT_EQ(1u, BWDecode.sortedStr[4].second);
}

TEST(BurrowsWheelerTransformTest, test4_decode)
{
    std::string str = "ABRACADABRA!";
    BurrowsWheelerTransform BWTransform(str);
    BurrowsWheelerDecode BWDecode(BWTransform.getOriginalStringRow(), BWTransform.getTransformedStr());
    EXPECT_TRUE(str == BWDecode.getOriginalString());
}

TEST(BurrowsWheelerTransformTest, test4_checkNext)
{
    std::string str = "ABRACADABRA!";
    BurrowsWheelerTransform BWTransform(str);
    BurrowsWheelerDecodeFake BWDecode(BWTransform.getOriginalStringRow(), BWTransform.getTransformedStr());
    EXPECT_EQ(3u, BWDecode.sortedStr[0].second);
    EXPECT_EQ(0u, BWDecode.sortedStr[1].second);
    EXPECT_EQ(6u, BWDecode.sortedStr[2].second);
    EXPECT_EQ(7u, BWDecode.sortedStr[3].second);
    EXPECT_EQ(8u, BWDecode.sortedStr[4].second);
    EXPECT_EQ(9u, BWDecode.sortedStr[5].second);
    EXPECT_EQ(10u, BWDecode.sortedStr[6].second);
    EXPECT_EQ(11u, BWDecode.sortedStr[7].second);
    EXPECT_EQ(5u, BWDecode.sortedStr[8].second);
    EXPECT_EQ(2u, BWDecode.sortedStr[9].second);
    EXPECT_EQ(1u, BWDecode.sortedStr[10].second);
    EXPECT_EQ(4u, BWDecode.sortedStr[11].second);
}

TEST(BurrowsWheelerTransformTest, test5_stress)
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

    BurrowsWheelerTransform BWTransform(str);
    BurrowsWheelerDecode BWDecode(BWTransform.getOriginalStringRow(), BWTransform.getTransformedStr());
    EXPECT_TRUE(str == BWDecode.getOriginalString());
}
