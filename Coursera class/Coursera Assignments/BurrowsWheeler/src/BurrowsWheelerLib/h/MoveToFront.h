#pragma once

#include <list>
#include <vector>
#include <string>

class MoveToFront
{
public:
    typedef std::vector<unsigned char> encodedResult;
    typedef std::list<unsigned char> RadixArray;
    MoveToFront();

    static const unsigned char radix = 255;
    
    encodedResult encode(const std::string& input);
    std::string decode(const encodedResult& input);
protected:
    static RadixArray radixArray;
};
