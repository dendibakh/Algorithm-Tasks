#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include <stdexcept>

template<class T>
class Heap
{
private:
    void bubbleUp(size_t index)
    {
        size_t parent = 0;
        while (hasParent(index))
        {
            parent = getParent(index);
            if (array[index] < array[parent]) 
                std::swap(array[index], array[parent]);
            index = parent;
        }
    }

    void bubbleDown(size_t index)
    {
        size_t left = getLeftChild(index);
        size_t right = getRightChild(index);
        size_t arSize = array.size();
        size_t indexToSwap = 0;

        while ( left < arSize || right < arSize ) // there are childrens
        {
            if (left < arSize && right < arSize)
            {
                if (array[left] < array[right])
                    indexToSwap = left;
                else
                    indexToSwap = right;
            }
            else if (left < arSize)
            {
                indexToSwap = left;
            }
            else if (right < arSize)
            {
                indexToSwap = right;
            }

            if ( array[index] <= array[indexToSwap] ) // we are done
                break;

            std::swap(array[index], array[indexToSwap]);

            index = indexToSwap;
            left = getLeftChild(index);
            right = getRightChild(index);
        }
    }

    void PrintArray()
    {
        for (size_t i = 0; i < array.size(); ++i )
        {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

public:
    Heap() 
    {
    }

    template <class U>
    Heap(const U& source) 
    {
        array.insert(array.begin(), source.begin(), source.end());
        size_t N = array.size();
        for (size_t i = 0; i < N; ++i )
        {
            bubbleDown(N - i - 1);
        }
    }
    
    void insert(const T& val)
    {
        array.push_back(val);
        bubbleUp(array.size() - 1);
    } 

    T deleteMin()
    {
        if (array.empty())
            throw std::runtime_error("You are trying to extract from empty heap!");
        T val = array.front();
        std::swap(array.back(), array.front());
        array.pop_back();
        bubbleDown(0);
        return val;
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
