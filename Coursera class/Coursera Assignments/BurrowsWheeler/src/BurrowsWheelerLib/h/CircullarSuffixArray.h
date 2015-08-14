#pragma once

#include "3WayRadixQuickSort.h"

class CircullarSuffixArray
{
    bool validate() const;
public:
    CircullarSuffixArray(const std::string& str);
    size_t getLenght() const;
    size_t getIndex(size_t i) const;
    const CircullarIndexStrSet& getSet() const;
protected:
    CircullarIndexStrSet circSuffixArray;
};
