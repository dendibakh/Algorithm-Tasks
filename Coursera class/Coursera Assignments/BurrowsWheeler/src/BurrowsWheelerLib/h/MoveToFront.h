#pragma once

#include <list>
#include <string>

class MoveToFront
{
public:
    typedef std::list<unsigned char> encodedResult;
    MoveToFront();

    static const unsigned char radix = 255;
    
    encodedResult encode(const std::string& input);
    std::string decode(const encodedResult& input);
protected:
    static encodedResult radixArray;
};
