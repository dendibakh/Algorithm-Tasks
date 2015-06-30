#include <algorithm>

int solution(vector<int> &A)
{
   if (A.size() < 3)
      return 0;
   std::sort(A.begin(), A.end());
   for (vector<int>::const_iterator iter = A.begin() + 2; iter != A.end(); ++iter)
   {
      if (*(iter-1) + *(iter-2) > *(iter))
         return 1;
   }
   return 0;
}