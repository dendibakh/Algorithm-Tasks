#include "gtest/gtest.h"
#include "3WayRadixQuickSort.h"

using namespace testing;
using namespace std;

TEST(ThreeWayRadixQuickSort, constructCircSuffixArray)
{
    std::string str = "ABRA!";
    CircullarIndexStrSet circSuffixArray;

    size_t N = str.size();
    for (size_t i = 0; i < N; ++i)
        circSuffixArray.push_back(CircullarIndexString(str, i));

    CircullarIndexStrSet etalonCircSuffixArray;
    std::string one("ABRA!");
    std::string two("BRA!A");
    std::string three("RA!AB");
    std::string four("A!ABR");
    std::string five("!ABRA");
    etalonCircSuffixArray.push_back(one);
    etalonCircSuffixArray.push_back(two);
    etalonCircSuffixArray.push_back(three);
    etalonCircSuffixArray.push_back(four);
    etalonCircSuffixArray.push_back(five);

    for (size_t i = 0; i < N; ++i)
        EXPECT_TRUE(circSuffixArray[i] == etalonCircSuffixArray[i]);
}

TEST(ThreeWayRadixQuickSort, sortCircSuffixArray)
{
    std::string str = "ABRA!";
    CircullarIndexStrSet circSuffixArray;

    size_t N = str.size();
    for (size_t i = 0; i < N; ++i)
        circSuffixArray.push_back(CircullarIndexString(str, i));

    ThreeWayRadixQuickSort_NoConst(circSuffixArray);

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

    for (size_t i = 0; i < N; ++i)
        EXPECT_TRUE(circSuffixArray[i] == etalonSortedCircSuffixArray[i]);
}

TEST(ThreeWayRadixQuickSort, sortCircSuffixArray_emptyString)
{
    std::string str = "";
    CircullarIndexStrSet circSuffixArray;

    size_t N = str.size();
    for (size_t i = 0; i < N; ++i)
        circSuffixArray.push_back(CircullarIndexString(str, i));

    CircullarIndexStrSet sortedCircSuffixArray = ThreeWayRadixQuickSort(circSuffixArray);

    CircullarIndexStrSet etalonSortedCircSuffixArray;

    for (size_t i = 0; i < N; ++i)
        EXPECT_TRUE(sortedCircSuffixArray[i] == etalonSortedCircSuffixArray[i]);
}

TEST(ThreeWayRadixQuickSort, sortCircSuffixArray_OneSymbol)
{
    std::string str = "!";
    CircullarIndexStrSet circSuffixArray;

    size_t N = str.size();
    for (size_t i = 0; i < N; ++i)
        circSuffixArray.push_back(CircullarIndexString(str, i));

    CircullarIndexStrSet sortedCircSuffixArray = ThreeWayRadixQuickSort(circSuffixArray);

    CircullarIndexStrSet etalonSortedCircSuffixArray;
    std::string one("!");
    etalonSortedCircSuffixArray.push_back(one);

    for (size_t i = 0; i < N; ++i)
        EXPECT_TRUE(sortedCircSuffixArray[i] == etalonSortedCircSuffixArray[i]);
}
