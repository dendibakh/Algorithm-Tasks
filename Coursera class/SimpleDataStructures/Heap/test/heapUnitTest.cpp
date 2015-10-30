#include "gtest/gtest.h"
#include "heap.h"
#include <limits>

using namespace testing;

class FakeIntHeap : public Heap<int>
{
public:
    using Heap<int>::array;
};

template <class T>
void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
{
     EXPECT_EQ(lhs.size(), rhs.size());
     EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

TEST(HeapUnitTest, 1)
{
     FakeIntHeap heap;
     (void)heap;
}

TEST(HeapUnitTest, 2)
{
     FakeIntHeap heap;
     heap.insert(1);
     checkTwoVectorsAreEqual({1}, heap.array);
}

TEST(HeapUnitTest, 3)
{
     FakeIntHeap heap;
     heap.insert(0);
     checkTwoVectorsAreEqual({0}, heap.array);
}

TEST(HeapUnitTest, 4)
{
     FakeIntHeap heap;
     heap.insert(std::numeric_limits<int>::max());
     checkTwoVectorsAreEqual({std::numeric_limits<int>::max()}, heap.array);
}

TEST(HeapUnitTest, 5)
{
     FakeIntHeap heap;
     heap.insert(0);
     heap.insert(1);
     checkTwoVectorsAreEqual({0, 1}, heap.array);
}

TEST(HeapUnitTest, 6)
{
     FakeIntHeap heap;
     heap.insert(0);
     heap.insert(1);
     heap.insert(2);
     checkTwoVectorsAreEqual({0, 1, 2}, heap.array);
}

TEST(HeapUnitTest, 7)
{
     FakeIntHeap heap;
     heap.insert(2);
     heap.insert(1);
     //checkTwoVectorsAreEqual({1, 2}, heap.array);
}

TEST(HeapUnitTest, 8)
{
    EXPECT_EQ(1, FakeIntHeap::getLeftChild(0));
    EXPECT_EQ(2, FakeIntHeap::getRightChild(0));

    EXPECT_EQ(3, FakeIntHeap::getLeftChild(1));
    EXPECT_EQ(4, FakeIntHeap::getRightChild(1));

    EXPECT_EQ(5, FakeIntHeap::getLeftChild(2));
    EXPECT_EQ(6, FakeIntHeap::getRightChild(2));
}

TEST(HeapUnitTest, 9)
{
    EXPECT_EQ(std::numeric_limits<size_t>::max(), FakeIntHeap::getParent(0));
    EXPECT_EQ(2, FakeIntHeap::getParent(6));
    EXPECT_EQ(2, FakeIntHeap::getParent(5));
    EXPECT_EQ(1, FakeIntHeap::getParent(4));
    EXPECT_EQ(1, FakeIntHeap::getParent(3));
    EXPECT_EQ(0, FakeIntHeap::getParent(2));
    EXPECT_EQ(0, FakeIntHeap::getParent(1));
    EXPECT_EQ(0, FakeIntHeap::getParent(FakeIntHeap::getParent(6)));
    EXPECT_EQ(std::numeric_limits<size_t>::max(), FakeIntHeap::getParent(FakeIntHeap::getParent(FakeIntHeap::getParent(6))));
}

TEST(HeapUnitTest, 10)
{
    size_t counter = 0;

    size_t parent = 6;
    while (FakeIntHeap::isLegalParent(parent))
    {
        parent = FakeIntHeap::getParent(parent);
        ++counter;
    }

    ASSERT_EQ(3, counter);
}

TEST(HeapUnitTest, 11)
{
    size_t counter = 0;

    size_t parent = 6;
    while (FakeIntHeap::hasParent(parent))
    {
        parent = FakeIntHeap::getParent(parent);
        ++counter;
    }

    ASSERT_EQ(2, counter);
}
