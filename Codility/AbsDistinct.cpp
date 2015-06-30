#include <limits>
#include <vector>

using namespace std;

int solution(vector<int>& A) 
{
   const int N = static_cast<int>(A.size());
   int count = 1;
   unsigned int prevI = numeric_limits<int>::max();
   unsigned int prevJ = numeric_limits<int>::min();
   unsigned int absI = 0;
   unsigned int absJ = 0;
   for (int i = 0, j = N - 1; i != j;)
   {
      absI = ( A[i] == numeric_limits<int>::min() ) ? abs(A[i] + 1) + 1 : abs(A[i]);
      absJ = ( A[j] == numeric_limits<int>::min() ) ? abs(A[j] + 1) + 1 : abs(A[j]);

      if (absI == prevI)
      {
         prevI = absI;
         i++;
         continue;
      }
      if (absJ == prevJ)
      {
         prevJ = absJ;
         j--;
         continue;
      }
      if (absI == absJ)
      {
         prevI = absI;
         i++;
         continue;
      }
      
      count++;
      if (absI > absJ)
      {
         prevI = absI;
         i++;
      }
      else
      {
         prevJ = absJ;
         j--;
      }
   }
   return count;
}

int main()
{
   int arr[] = {numeric_limits<int>::min(), numeric_limits<int>::min(), -5, -3, -1, -1, 0, 3, 3, 6};
   size_t sizeArr = sizeof(arr) / sizeof(arr[0]);
   vector<int> vect(arr, arr + sizeArr);
   int res = solution(vect);
}
