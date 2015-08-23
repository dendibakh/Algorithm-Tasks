#include "BurrowsWheelerTransform.h"
#include <algorithm> 

BurrowsWheelerTransform::BurrowsWheelerTransform(const std::string& str) : suffixArray(str) , originalStringRow(0) , transformedStr(str.size(), 0)
{
    size_t N = suffixArray.getSet().size();
    for (size_t i = 0; i < N; ++i)
    {
        if (suffixArray.getSet()[i].getBegin() == 0)
            originalStringRow = i;
        transformedStr[i] = suffixArray.getSet()[i][N - 1];
    }
}

BurrowsWheelerTransform::~BurrowsWheelerTransform()
{

}

size_t BurrowsWheelerTransform::getOriginalStringRow() const
{
    return originalStringRow;
}

const std::string& BurrowsWheelerTransform::getTransformedStr() const
{
    return transformedStr;
}

BurrowsWheelerDecode::BurrowsWheelerDecode(size_t originalStringRow, const std::string& str) : originalString(str.size(), 0), sortedStr(str.size())
{
    size_t N = str.size();
    for (size_t i = 0; i < N; ++i)
    {
        sortedStr[i].first = str[i];
        sortedStr[i].second = i;
    }
    
    std::stable_sort(sortedStr.begin(), sortedStr.end(), comparator());

    size_t curElem = originalStringRow;
    for (size_t i = 0; i < N; ++i)
    {
        originalString[i] = sortedStr[curElem].first;
        curElem = sortedStr[curElem].second;
    }
}

BurrowsWheelerDecode::~BurrowsWheelerDecode()
{
}

std::string BurrowsWheelerDecode::getOriginalString() const
{
    return originalString;
}
