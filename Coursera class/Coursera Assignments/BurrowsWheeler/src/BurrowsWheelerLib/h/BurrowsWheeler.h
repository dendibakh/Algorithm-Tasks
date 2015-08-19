#pragma once

#include "HuffmanCompression.h"

class BurrowsWheeler
{
public:
    typedef HuffmanAlgorithm::compressedResult compressedResult;

    BurrowsWheeler();
    virtual ~BurrowsWheeler();

    compressedResult encode(const std::string& text);
    std::string decode(const compressedResult& compressedText);
};
