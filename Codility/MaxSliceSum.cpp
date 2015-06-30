#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int solution(const vector<int> &A) 
{
   const int N = static_cast<int>(A.size());
   int maxSum = numeric_limits<int>::min();
   int curSum = 0;
   for (int i = 0; i < N; i++)
   {
      if (curSum + A[i] > numeric_limits<int>::max())
         return numeric_limits<int>::max();
      if (curSum + A[i] < numeric_limits<int>::min())
         curSum = numeric_limits<int>::min();
      curSum = curSum + A[i];
      maxSum = max(maxSum, curSum);
      curSum = max(0, curSum);
   }

   return maxSum;
}

int main()
{
   int arr1[] = {3, 2, -6, 4, 0};
   int arr2[] = {-10};
   int arr3[] = {-2, -10};
   int arr4[] = {-5, -2, -10};
   int result1 = solution(vector<int>(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0])));
   int result2 = solution(vector<int>(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0])));
   int result3 = solution(vector<int>(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0])));
   int result4 = solution(vector<int>(arr4, arr4 + sizeof(arr4) / sizeof(arr4[0])));
   //system("pause");
}