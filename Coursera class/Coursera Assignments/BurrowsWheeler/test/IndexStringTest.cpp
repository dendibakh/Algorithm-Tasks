#include "gtest/gtest.h"
#include "IndexString.h"

using namespace testing;
using namespace std;

TEST(IndexStringTest, test1)
{
    string InitSet("We think in generalities, but we live in details.");
    IndexString indexStr(InitSet, 12, 24);
    
    string etalon("generalities");

    string actual(indexStr.getString());
    EXPECT_TRUE(std::equal(etalon.begin(), etalon.end(), actual.begin()));
}

TEST(IndexStringTest, test2)
{
    string InitSet("We think in generalities, but we live in details.");
    IndexString indexStr(InitSet, 4, 9);

    string etalon("hink ");

    string actual(indexStr.getString());
    EXPECT_TRUE(std::equal(etalon.begin(), etalon.end(), actual.begin()));
}

TEST(IndexStringTest, test3)
{
    string InitSet("We think in generalities, but we live in details.");
    IndexString indexStr(InitSet, 4, 9);
    IndexString copyIndexStr(indexStr);

    string etalon("hink ");

    string actual(copyIndexStr.getString());
    EXPECT_TRUE(std::equal(etalon.begin(), etalon.end(), actual.begin()));
}

TEST(IndexStringTest, test4)
{
    string InitSet("We think in generalities, but we live in details.");
    IndexString indexStr(InitSet, 4, 9);
    IndexString copyIndexStr(InitSet, 3, 8);

    string etalon1("think");
    string actual1(copyIndexStr.getString());
    EXPECT_TRUE(std::equal(etalon1.begin(), etalon1.end(), actual1.begin()));

    string etalon2("hink ");
    copyIndexStr = indexStr;
    string actual2(copyIndexStr.getString());
    EXPECT_TRUE(std::equal(etalon2.begin(), etalon2.end(), actual2.begin()));
}

TEST(IndexStringTest, testExchangeStrings)
{
    string InitString("think");
    IndexString indexStr(InitString);
    string copyString("generalities");
    IndexString copyIndexStr(copyString);

    IndexString temp(copyIndexStr);
    copyIndexStr = indexStr;
    indexStr = temp;

    string actualStr(indexStr.getString());
    string actualIndexStr(copyIndexStr.getString());
    EXPECT_TRUE(std::equal(copyString.begin(), copyString.end(), actualStr.begin()));
    EXPECT_TRUE(std::equal(InitString.begin(), InitString.end(), actualIndexStr.begin()));
}

TEST(IndexStringTest, test6)
{
    string InitSet("We think in generalities, but we live in details.");
    IndexString copyIndexStr(InitSet, 3, 8);
    			
    EXPECT_TRUE(copyIndexStr[0] == 't');
    EXPECT_TRUE(copyIndexStr[1] == 'h');
    EXPECT_TRUE(copyIndexStr[2] == 'i');
    EXPECT_TRUE(copyIndexStr[3] == 'n');
    EXPECT_TRUE(copyIndexStr[4] == 'k');
}
