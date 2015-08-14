#include "gtest/gtest.h"
#include "CircullarSuffixArray.h"

using namespace testing;
using namespace std;

class CircullarSuffixArrayFake : public CircullarSuffixArray
{
public:
    CircullarSuffixArrayFake(const std::string& str) : CircullarSuffixArray(str) {}
    using CircullarSuffixArray::circSuffixArray;
};

TEST(CircullarSuffixArrayTest, test1)
{
    std::string str = "ABRA!";
    CircullarSuffixArrayFake array(str);

    CircullarIndexStrSet etalonSortedCircSuffixArray;
    std::string one("!ABRA");
    std::string two("A!ABR");
    std::string three("ABRA!");
    std::string four("BRA!A");
    std::string five("RA!AB");
    etalonSortedCircSuffixArray.push_back(one);
    etalonSortedCircSuffixArray.push_back(two);
    etalonSortedCircSuffixArray.push_back(three);
    etalonSortedCircSuffixArray.push_back(four);
    etalonSortedCircSuffixArray.push_back(five);

    size_t N = str.size();
    for (size_t i = 0; i < N; ++i)
        EXPECT_TRUE(array.circSuffixArray[i] == etalonSortedCircSuffixArray[i]);
}

TEST(CircullarSuffixArrayTest, test2)
{
    std::string str = "ABRA!";
    CircullarSuffixArrayFake array(str);

    EXPECT_EQ(5u, array.getLenght());

    EXPECT_EQ(4u, array.getIndex(0u));
    EXPECT_EQ(3u, array.getIndex(1u));
    EXPECT_EQ(0u, array.getIndex(2u));
    EXPECT_EQ(1u, array.getIndex(3u));
    EXPECT_EQ(2u, array.getIndex(4u));

    try	
    {
        array.getIndex(5u);
        FAIL() << "There must be an exception";
    }
    catch(std::exception& e)
    {
    }
}

TEST(CircullarSuffixArrayTest, test3)
{
    std::string str = "";
    CircullarSuffixArrayFake array(str);

    EXPECT_EQ(0u, array.getLenght());

    try	
    {
        array.getIndex(0u);
        FAIL() << "There must be an exception";
    }
    catch(std::exception& e)
    {
    }
}
