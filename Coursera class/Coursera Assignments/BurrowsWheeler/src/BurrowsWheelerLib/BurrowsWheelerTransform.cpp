#include "BurrowsWheelerTransform.h"

BurrowsWheelerTransform::BurrowsWheelerTransform(const std::string& str) : suffixArray(str) , originalStringRow(0)
{
    size_t N = suffixArray.getSet().size();
    for (size_t i = 0; i < N; ++i)
    {
        if (suffixArray.getSet()[i].getBegin() == 0)
            originalStringRow = i;
        transformedStr += suffixArray.getSet()[i][N - 1];
    }
}

BurrowsWheelerTransform::~BurrowsWheelerTransform()
{

}

size_t BurrowsWheelerTransform::getOriginalStringRow() const
{
    return originalStringRow;
}

std::string BurrowsWheelerTransform::getTransformedStr() const
{
    return transformedStr;
}
