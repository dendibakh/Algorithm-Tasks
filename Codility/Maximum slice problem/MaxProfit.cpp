#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int solution(const vector<int> &A) 
{
   const int N = static_cast<int>(A.size());
   int maxProfit = 0;
   int minPrice  = numeric_limits<int>::max();
   for (int i = 0; i < N; i++)
   {
      if (A[i] < minPrice)
         minPrice = A[i];
      if (A[i] - minPrice > maxProfit)
         maxProfit = A[i] - minPrice;
   }

   return maxProfit;
}

int main()
{
   int arr[] = {23171, 21011, 21123, 21366, 21013, 21367};
   int result = solution(vector<int>(arr, arr + sizeof(arr) / sizeof(arr[0])));
   //system("pause");
}