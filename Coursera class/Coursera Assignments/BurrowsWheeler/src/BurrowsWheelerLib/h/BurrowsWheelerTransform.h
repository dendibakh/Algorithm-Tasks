#pragma once

#include "CircullarSuffixArray.h"

class BurrowsWheelerTransform
{
public:
    BurrowsWheelerTransform(const std::string& str);
    virtual ~BurrowsWheelerTransform();

    size_t getOriginalStringRow() const;
    std::string getTransformedStr() const;
private:
    CircullarSuffixArray suffixArray;
    size_t originalStringRow;
    std::string transformedStr;
};
