#pragma once
#include <vector>
#include <limits>

template<class T>
class Heap
{
public:
    Heap() {}
    void insert(const T& val)
    {
        array.push_back(val);
    } 

    static size_t getLeftChild(size_t index)
    {
        return 2 * index + 1;
    }

    static size_t getRightChild(size_t index)
    {
        return 2 * index + 2;
    }

    static size_t getParent(size_t index)
    {
        if (index == 0)
           return std::numeric_limits<size_t>::max(); 
        return (index - 1 ) / 2;
    }

    static bool isLegalParent(size_t index)
    {
        return index != std::numeric_limits<size_t>::max();
    }

    static bool hasParent(size_t index)
    {
        return index != 0;
    }

protected:
    std::vector<T> array;
};
