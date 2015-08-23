#include "CircullarSuffixArray.h"
#include <stdexcept>

CircullarSuffixArray::CircullarSuffixArray(const std::string& str) : circSuffixArray(CircullarIndexStrSet(str.size(), CircullarIndexString(str)))
{
    size_t N = str.size();
    for (size_t i = 0; i < N; ++i)
        circSuffixArray[i].getBegin() = i;

    if (validate())
        ThreeWayRadixQuickSort_NoConst(circSuffixArray);
}
 
size_t CircullarSuffixArray::getLenght() const
{
    if (!validate())
        return 0;
    return circSuffixArray[0].size();
}

size_t CircullarSuffixArray::getIndex(size_t i)
{
    if (!validate())
        throw std::runtime_error("Initial string is empty.");
    if (i >= getLenght())
        throw std::runtime_error("Provided index is not valid.");
    return circSuffixArray[i].getBegin();
}

bool CircullarSuffixArray::validate() const
{
    return 0 != circSuffixArray.size();
}

CircullarIndexStrSet& CircullarSuffixArray::getSet()
{
    return circSuffixArray;
}
