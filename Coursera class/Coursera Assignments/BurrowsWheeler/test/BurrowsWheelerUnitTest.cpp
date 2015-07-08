#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "BurrowsWheeler.h"

using namespace testing;

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
