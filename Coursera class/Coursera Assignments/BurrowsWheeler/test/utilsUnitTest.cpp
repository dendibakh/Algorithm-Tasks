#include "gtest/gtest.h"

#include "utils.h"
#include <algorithm>

using namespace testing;

template <class T>
void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
{
     EXPECT_EQ(lhs.size(), rhs.size());
     EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

TEST(utilsUnitTest, test1)
{
     bool expectedArray[] = { 0, 1, 0, 0, 0, 0, 0, 1};
     std::vector<bool> expected(expectedArray, expectedArray + sizeof(expectedArray) / sizeof(expectedArray[0]));

     std::vector<bool> actual = getBinaryRepresentation('A');
     checkTwoVectorsAreEqual(expected, actual);
}

TEST(utilsUnitTest, test2)
{
     bool expectedArray[] = { 0, 1, 0, 0, 1, 0, 0, 1 };
     std::vector<bool> expected(expectedArray, expectedArray + sizeof(expectedArray) / sizeof(expectedArray[0]));
     std::vector<bool> actual = getBinaryRepresentation('I');
     checkTwoVectorsAreEqual(expected, actual);
}

TEST(utilsUnitTest, test3)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 0, 0, 0, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ('A', getSymbol(binaryRepresentation));
}

TEST(utilsUnitTest, test4)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ('I', getSymbol(binaryRepresentation));
}

TEST(utilsUnitTest, test5)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ('\0', getSymbol(binaryRepresentation));
}

TEST(utilsUnitTest, test6)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 0, 0};
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ('\0', getSymbol(binaryRepresentation));
}

TEST(utilsUnitTest, test7)
{
     size_t value = 7u;
     std::vector<bool> binaryRepresentation(sizeof(value) * 8, 0);
     binaryRepresentation[5] = 1;
     binaryRepresentation[6] = 1;
     binaryRepresentation[7] = 1;
     checkTwoVectorsAreEqual(binaryRepresentation, getBinaryRepresentation(value));
}

TEST(utilsUnitTest, test8)
{
     size_t value = 0x20042020;
     std::vector<bool> binaryRepresentation(sizeof(value) * 8, 0);
     binaryRepresentation[2] = 1;
     binaryRepresentation[10] = 1;
     binaryRepresentation[21] = 1;
     binaryRepresentation[26] = 1;
     checkTwoVectorsAreEqual(binaryRepresentation, getBinaryRepresentation(value));
}

TEST(utilsUnitTest, test9)
{
     size_t value = 0x20042020;
     std::vector<bool> binaryRepresentation = getBinaryRepresentation(value);
     size_t expanded = getValue(binaryRepresentation);
     EXPECT_EQ(value, expanded);
}

TEST(utilsUnitTest, test10)
{
     size_t value = 0xDE17285F;
     std::vector<bool> binaryRepresentation = getBinaryRepresentation(value);
     size_t expanded = getValue(binaryRepresentation);
     EXPECT_EQ(value, expanded);
}
