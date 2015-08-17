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

MoveToFront::encodedResult MoveToFront::radixArray;

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
   encodedResult moveToFrontArray(radixArray);
   encodedResult result(N, 0);
   encodedResult::iterator iter = result.begin();
   for (size_t i = 0; i < N; ++i, ++iter)
   {
       unsigned char cur = input[i];
       unsigned char index = 0;
       for (encodedResult::iterator moveToFrontIter = moveToFrontArray.begin(); moveToFrontIter != moveToFrontArray.end(); ++moveToFrontIter, ++index)
       {
           if (cur == *moveToFrontIter)
           {
               moveToFrontArray.erase(moveToFrontIter);
               moveToFrontArray.push_front(cur);
               *iter = index;
               break;
           }
       }
   }
   return result;
}

std::string MoveToFront::decode(const encodedResult& input)
{
    return "";
}
