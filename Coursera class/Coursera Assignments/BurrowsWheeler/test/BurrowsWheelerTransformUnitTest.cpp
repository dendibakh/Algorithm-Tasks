#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "BurrowsWheelerTransform.h"

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
