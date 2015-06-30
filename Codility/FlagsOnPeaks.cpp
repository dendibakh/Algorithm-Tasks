#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

std::vector<int> getNearestFlags(vector<int>& A)
{
   const int N = static_cast<int>(A.size());
   std::vector<int> nearestFlag(N, -1);
   for (int i = N - 2; i >= 0; i--)
   {
      if ( (A[i] > A[i+1]) && (A[i] > A[i-1]) )
         nearestFlag[i] = i;
      else
         nearestFlag[i] = nearestFlag[i + 1];
   }
   return nearestFlag;
}

int solution(vector<int>& A) 
{
   const int N = static_cast<int>(A.size());
   std::vector<int> nearestFlag = getNearestFlags(A);
   int i = 1;
   int result = 0;
   while (i * i <= N)
   {
      int pos = 0;
      int num = 0;
      while ( (pos < N) && (num < i) )
      {
         pos = nearestFlag[pos];
         if (pos == -1)
            break;
         num += 1;
         pos += i;
      }
      result = max(result, num);
      i += 1;
   }
   return result;
}

int main()
{
   int arr1[] = {1, 5, 3, 4, 3, 1, 2, 3, 4, 6, 2};
   int result1 = solution(vector<int>(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0])));
   //system("pause");
}