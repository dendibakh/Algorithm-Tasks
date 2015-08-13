#include "gtest/gtest.h"
#include "CircullarIndexString.h"

using namespace testing;
using namespace std;

TEST(CircullarIndexStringTest, test1)
{
    string InitSet("We think in generalities, but we live in details.");
    CircullarIndexString indexStr(InitSet, 12);
    
    string etalon("generalities, but we live in details.We think in ");

    string actual(indexStr.getString());
    EXPECT_TRUE(std::equal(etalon.begin(), etalon.end(), actual.begin()));
}

TEST(CircullarIndexStringTest, test2)
{
    string InitSet("We think in generalities, but we live in details.");
    CircullarIndexString indexStr(InitSet, 4);

    string etalon("hink in generalities, but we live in details.We t");

    string actual(indexStr.getString());
    EXPECT_TRUE(std::equal(etalon.begin(), etalon.end(), actual.begin()));
}

TEST(CircullarIndexStringTest, test3)
{
    string InitSet("We think in generalities, but we live in details.");
    CircullarIndexString indexStr(InitSet, 4);
    CircullarIndexString copyIndexStr(indexStr);

    string etalon("hink in generalities, but we live in details.We t");

    string actual(copyIndexStr.getString());
    EXPECT_TRUE(std::equal(etalon.begin(), etalon.end(), actual.begin()));
}

TEST(CircullarIndexStringTest, test4)
{
    string InitSet("We think in generalities, but we live in details.");
    CircullarIndexString indexStr(InitSet, 4);
    CircullarIndexString copyIndexStr(InitSet, 3);

    string etalon1("think in generalities, but we live in details.We ");
    string actual1(copyIndexStr.getString());
    EXPECT_TRUE(std::equal(etalon1.begin(), etalon1.end(), actual1.begin()));

    string etalon2("hink in generalities, but we live in details.We t");
    copyIndexStr = indexStr;
    string actual2(copyIndexStr.getString());
    EXPECT_TRUE(std::equal(etalon2.begin(), etalon2.end(), actual2.begin()));
}

TEST(CircullarIndexStringTest, testExchangeStrings)
{
    string InitString("think");
    CircullarIndexString indexStr(InitString);
    string copyString("generalities");
    CircullarIndexString copyIndexStr(copyString);

    CircullarIndexString temp(copyIndexStr);
    copyIndexStr = indexStr;
    indexStr = temp;

    string actualStr(indexStr.getString());
    string actualIndexStr(copyIndexStr.getString());
    EXPECT_TRUE(std::equal(copyString.begin(), copyString.end(), actualStr.begin()));
    EXPECT_TRUE(std::equal(InitString.begin(), InitString.end(), actualIndexStr.begin()));
}

TEST(CircullarIndexStringTest, test6)
{
    string InitSet("We think in generalities, but we live in details.");
    CircullarIndexString copyIndexStr(InitSet, 3);
    			
    EXPECT_TRUE(copyIndexStr[0] == 't');
    EXPECT_TRUE(copyIndexStr[1] == 'h');
    EXPECT_TRUE(copyIndexStr[2] == 'i');
    EXPECT_TRUE(copyIndexStr[3] == 'n');
    EXPECT_TRUE(copyIndexStr[4] == 'k');

    EXPECT_TRUE(copyIndexStr[InitSet.size() - 3] == 'W');
    EXPECT_TRUE(copyIndexStr[InitSet.size() - 2] == 'e');
    EXPECT_TRUE(copyIndexStr[InitSet.size() - 1] == ' ');
    EXPECT_TRUE(copyIndexStr[InitSet.size()] == 't');
    EXPECT_TRUE(copyIndexStr[InitSet.size() + InitSet.size()] == 't');

    EXPECT_TRUE(copyIndexStr[-1] == ' '); // (4294967294 + 3) mod InitSet.size()
}
