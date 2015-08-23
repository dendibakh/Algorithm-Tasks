#pragma once

#include "CircullarSuffixArray.h"

class BurrowsWheelerTransform
{
public:
    BurrowsWheelerTransform(const std::string& str);
    virtual ~BurrowsWheelerTransform();

    size_t getOriginalStringRow() const;
    const std::string& getTransformedStr() const;
private:
    CircullarSuffixArray suffixArray;
    size_t originalStringRow;
    std::string transformedStr;
};

class BurrowsWheelerDecode
{
public:
    typedef std::pair<unsigned char, size_t> elem;
private:
    struct comparator
    {
        bool operator()(const elem& lhs, const elem& rhs) const
        {
            return lhs.first < rhs.first;
        }
    };
public:
    BurrowsWheelerDecode(size_t originalStringRow, const std::string& str);
    virtual ~BurrowsWheelerDecode();

    std::string getOriginalString() const;
private:
    std::string originalString;
protected:
    std::vector<elem> sortedStr;
};
