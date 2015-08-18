#include "MoveToFront.h"
#include <algorithm>

namespace
{
    struct UniqueNumber
    {
        UniqueNumber() { current = 0;}
        int current;
        int operator()() { return current++; }
    };
}

MoveToFront::RadixArray MoveToFront::radixArray;

MoveToFront::MoveToFront()
{
   if (radixArray.empty())
   {
      radixArray.resize(radix);
      std::generate(radixArray.begin(), radixArray.end(), UniqueNumber());
   }
}

MoveToFront::encodedResult MoveToFront::encode(const std::string& input)
{
   size_t N = input.size();
   RadixArray moveToFrontArray(radixArray);
   encodedResult result(N, 0);
   for (size_t i = 0; i < N; ++i)
   {
       unsigned char cur = input[i];
       unsigned char index = 0;
       for (RadixArray::iterator moveToFrontIter = moveToFrontArray.begin(); moveToFrontIter != moveToFrontArray.end(); ++moveToFrontIter, ++index)
       {
           if (cur == *moveToFrontIter)
           {
               moveToFrontArray.erase(moveToFrontIter);
               moveToFrontArray.push_front(cur);
               result[i] = index;
               break;
           }
       }
   }
   return result;
}

std::string MoveToFront::decode(const encodedResult& input)
{
   size_t N = input.size();
   std::string decodedStr(N, '\0');
   RadixArray moveToFrontArray(radixArray);
   for (size_t i = 0; i < N; ++i)
   {
      unsigned char curIndex = input[i];
      RadixArray::iterator moveToFrontIter = moveToFrontArray.begin();
      for (unsigned char index = 0; moveToFrontIter != moveToFrontArray.end(); ++moveToFrontIter, ++index)
      {
         if (curIndex == index)
         {
             unsigned char symbolToFront = *moveToFrontIter;
             moveToFrontArray.erase(moveToFrontIter);
             moveToFrontArray.push_front(symbolToFront);
             decodedStr[i] = symbolToFront;
             break;
         }
      }
   }
   return decodedStr;
}
