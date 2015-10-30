#include "gtest/gtest.h"
#include "heap.h"
#include <limits>

using namespace testing;

class FakeIntHeap : public Heap<int>
{
public:
    FakeIntHeap() : Heap<int>() {}
    template <class U>
    FakeIntHeap(const U& source) : Heap<int>(source) { }
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
     checkTwoVectorsAreEqual({1, 2}, heap.array);
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

TEST(HeapUnitTest, 12)
{
    FakeIntHeap heap;
    heap.insert(2);
    heap.insert(1);
    heap.insert(0);
    checkTwoVectorsAreEqual({0, 2, 1}, heap.array);
}

TEST(HeapUnitTest, 13)
{
    // Skiena example
    FakeIntHeap heap;
    heap.insert(1804);
    heap.insert(1776);
    heap.insert(1492);
    heap.insert(2001);
    heap.insert(1963);
    heap.insert(1918);
    heap.insert(1783);
    heap.insert(1945);
    heap.insert(1865);
    heap.insert(1941);
    checkTwoVectorsAreEqual({1492, 1804, 1776, 1865, 1941, 1918, 1783, 2001, 1945, 1963}, heap.array);
}

TEST(HeapUnitTest, 14)
{
    // Skiena example with duplicates
    FakeIntHeap heap;
    heap.insert(1804);
    heap.insert(1776);
    heap.insert(1492);
    heap.insert(2001);
    heap.insert(1963);
    heap.insert(1918);
    heap.insert(1783);
    heap.insert(1945);
    heap.insert(1865);
    heap.insert(1941);
    heap.insert(1941);
    heap.insert(1941);
    heap.insert(1941);
    checkTwoVectorsAreEqual({1492, 1804, 1776, 1865, 1941, 1918, 1783, 2001, 1945, 1963, 1941, 1941, 1941}, heap.array);
}

TEST(HeapUnitTest, 15)
{
    // Skiena example
    FakeIntHeap heap;
    heap.insert(1804);
    heap.insert(1776);
    heap.insert(1492);
    heap.insert(2001);
    heap.insert(1963);
    heap.insert(1918);
    heap.insert(1783);
    heap.insert(1945);
    heap.insert(1865);
    heap.insert(1941);
    checkTwoVectorsAreEqual({1492, 1804, 1776, 1865, 1941, 1918, 1783, 2001, 1945, 1963}, heap.array);
    ASSERT_EQ(1492, heap.deleteMin());
}

TEST(HeapUnitTest, 16)
{
     FakeIntHeap heap;
     heap.insert(2);
     heap.insert(1);
     checkTwoVectorsAreEqual({1, 2}, heap.array);
     ASSERT_EQ(1, heap.deleteMin());
     checkTwoVectorsAreEqual({2}, heap.array);
     ASSERT_EQ(2, heap.deleteMin());
     checkTwoVectorsAreEqual({}, heap.array);
}

TEST(HeapUnitTest, 17)
{
     FakeIntHeap heap;
     heap.insert(2);
     heap.insert(1);
     heap.insert(0);
     checkTwoVectorsAreEqual({0, 2, 1}, heap.array);
     ASSERT_EQ(0, heap.deleteMin());
     checkTwoVectorsAreEqual({1, 2}, heap.array);
     ASSERT_EQ(1, heap.deleteMin());
     checkTwoVectorsAreEqual({2}, heap.array);
     ASSERT_EQ(2, heap.deleteMin());
     checkTwoVectorsAreEqual({}, heap.array);
}

TEST(HeapUnitTest, 18)
{
    // Skiena example
    FakeIntHeap heap;
    heap.insert(1804);
    heap.insert(1776);
    heap.insert(1492);
    heap.insert(2001);
    heap.insert(1963);
    heap.insert(1918);
    heap.insert(1783);
    heap.insert(1945);
    heap.insert(1865);
    heap.insert(1941);
    checkTwoVectorsAreEqual({1492, 1804, 1776, 1865, 1941, 1918, 1783, 2001, 1945, 1963}, heap.array);
    ASSERT_EQ(1492, heap.deleteMin());
    ASSERT_EQ(1776, heap.deleteMin());
    ASSERT_EQ(1783, heap.deleteMin());
    ASSERT_EQ(1804, heap.deleteMin());
    ASSERT_EQ(1865, heap.deleteMin());
    ASSERT_EQ(1918, heap.deleteMin());
    ASSERT_EQ(1941, heap.deleteMin());
    ASSERT_EQ(1945, heap.deleteMin());
    ASSERT_EQ(1963, heap.deleteMin());
    ASSERT_EQ(2001, heap.deleteMin());
}

TEST(HeapUnitTest, 19)
{
    std::vector<int> source = { 1804, 1776, 1492, 2001, 1963, 1918, 1783 };
    FakeIntHeap heap(source);
    
    checkTwoVectorsAreEqual({1492, 1776, 1783, 2001, 1963, 1918, 1804}, heap.array);
    ASSERT_EQ(1492, heap.deleteMin());
    ASSERT_EQ(1776, heap.deleteMin());
    ASSERT_EQ(1783, heap.deleteMin());
    ASSERT_EQ(1804, heap.deleteMin());
    ASSERT_EQ(1918, heap.deleteMin());
    ASSERT_EQ(1963, heap.deleteMin());
    ASSERT_EQ(2001, heap.deleteMin());
}

TEST(HeapUnitTest, 20)
{
    std::vector<int> source = { 1804, 1776, 1492, 2001, 1963, 1918, 1783, 1945, 1865, 1941 };
    FakeIntHeap heap(source);

    std::vector<int> expectedResult = { 1492, 1776, 1783, 1804, 1865, 1918, 1941, 1945, 1963, 2001 };
    
    std::vector<int> actualResult;
    while (!heap.array.empty())
    {
       actualResult.push_back(heap.deleteMin());
    }

    checkTwoVectorsAreEqual(expectedResult, actualResult);
}

TEST(HeapUnitTest, 21)
{
    std::vector<int> source = { };
    FakeIntHeap heap(source);

    try
    {
       heap.deleteMin();
       FAIL() << "There must be an exception";
    }
    catch(std::exception& e)
    {
    }
}
