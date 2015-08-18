#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MoveToFront.h"

#include <iostream>

using namespace testing;

template <class T>
void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
{
    EXPECT_EQ(lhs.size(), rhs.size());
    EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

class MoveToFrontFake : public MoveToFront
{
public:
    MoveToFrontFake() : MoveToFront() {}
    using MoveToFront::radixArray;

    void fakeArray()
    {
        save = MoveToFrontFake::radixArray;
        MoveToFrontFake::radixArray.clear();
        MoveToFrontFake::radixArray.push_back('A');
        MoveToFrontFake::radixArray.push_back('B');
        MoveToFrontFake::radixArray.push_back('C');
        MoveToFrontFake::radixArray.push_back('D');
        MoveToFrontFake::radixArray.push_back('E');
        MoveToFrontFake::radixArray.push_back('F');
    }

    void restoreArray()
    {
        MoveToFrontFake::radixArray = save;
    }

    MoveToFrontFake::RadixArray save;
};

TEST(MoveToFrontTest, testEncode1)
{
    std::string str = "CAAABCCCACCF";
    MoveToFrontFake moveToFront;
    
    unsigned char etalonAr[] = {2, 1, 0, 0, 2, 2, 0, 0, 2, 1, 0, 5};
    MoveToFrontFake::encodedResult etalon(etalonAr, etalonAr + sizeof(etalonAr) / sizeof(etalonAr[0]) );

    moveToFront.fakeArray();
    checkTwoVectorsAreEqual(etalon, moveToFront.encode(str));
    moveToFront.restoreArray();
}

TEST(MoveToFrontTest, testEncode2)
{
    std::string str = "ABRACADABRA!";
    MoveToFrontFake moveToFront;
    
    unsigned char etalonAr[] = {0x41, 0x42, 0x52, 0x2, 0x44, 0x1, 0x45, 0x1, 0x4, 0x4, 0x2, 0x26};
    MoveToFrontFake::encodedResult etalon(etalonAr, etalonAr + sizeof(etalonAr) / sizeof(etalonAr[0]) );

    /*
    MoveToFrontFake::encodedResult temp = moveToFront.encode(str);
    for (MoveToFrontFake::encodedResult::iterator i = temp.begin(); i != temp.end(); ++i)
    {
        std::cout << (unsigned int) *i;
    }
    */
    checkTwoVectorsAreEqual(etalon, moveToFront.encode(str));
}

TEST(MoveToFrontTest, testDecode1)
{
    unsigned char encodedStringArr[] = {2, 1, 0, 0, 2, 2, 0, 0, 2, 1, 0, 5};
    MoveToFrontFake::encodedResult encodedString(encodedStringArr, encodedStringArr + sizeof(encodedStringArr) / sizeof(encodedStringArr[0]) );

    MoveToFrontFake moveToFront;
    moveToFront.fakeArray();
    std::string etalon = "CAAABCCCACCF";
    EXPECT_TRUE(etalon == moveToFront.decode(encodedString));
    moveToFront.restoreArray();
}

TEST(MoveToFrontTest, testDecode2)
{
    unsigned char encodedStringArr[] = {0x41, 0x42, 0x52, 0x2, 0x44, 0x1, 0x45, 0x1, 0x4, 0x4, 0x2, 0x26};
    MoveToFrontFake::encodedResult encodedString(encodedStringArr, encodedStringArr + sizeof(encodedStringArr) / sizeof(encodedStringArr[0]) );

    MoveToFrontFake moveToFront;
    std::string etalon = "ABRACADABRA!";
    EXPECT_TRUE(etalon == moveToFront.decode(encodedString));
}

TEST(MoveToFrontTest, testEncodeDecode1)
{
    std::string str = "CAAABCCCACCF";
    MoveToFrontFake moveToFront;
    moveToFront.fakeArray();
    MoveToFrontFake::encodedResult encodedStr = moveToFront.encode(str);
    EXPECT_TRUE(str == moveToFront.decode(encodedStr));
    moveToFront.restoreArray();
}

TEST(MoveToFrontTest, testEncodeDecode2)
{
    std::string str = "ABRACADABRA!";
    MoveToFrontFake moveToFront;
    MoveToFrontFake::encodedResult encodedStr = moveToFront.encode(str);
    EXPECT_TRUE(str == moveToFront.decode(encodedStr));
}

TEST(MoveToFrontTest, testEncodeDecode3)
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
    MoveToFrontFake moveToFront;
    MoveToFrontFake::encodedResult encodedStr = moveToFront.encode(str);
    EXPECT_TRUE(str == moveToFront.decode(encodedStr));
}
