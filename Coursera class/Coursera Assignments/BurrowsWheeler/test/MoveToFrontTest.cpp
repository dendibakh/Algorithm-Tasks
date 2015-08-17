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

    MoveToFrontFake::encodedResult save;
};

TEST(MoveToFrontTest, test1)
{
    std::string str = "CAAABCCCACCF";
    MoveToFrontFake moveToFront;
    
    unsigned char etalonAr[] = {2, 1, 0, 0, 2, 2, 0, 0, 2, 1, 0, 5};
    MoveToFrontFake::encodedResult etalon(etalonAr, etalonAr + sizeof(etalonAr) / sizeof(etalonAr[0]) );

    moveToFront.fakeArray();
    checkTwoVectorsAreEqual(etalon, moveToFront.encode(str));
    moveToFront.restoreArray();
}

TEST(MoveToFrontTest, test2)
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
