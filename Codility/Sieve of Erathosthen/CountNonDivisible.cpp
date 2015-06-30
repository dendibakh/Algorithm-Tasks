#include <vector>

using namespace std;

vector<int> solution(vector<int> &A) 
{
   const int N = static_cast<int>(A.size());
   vector<int> count(2 * N + 1, 0);
   for (int i = 0; i < N; i++)
   {
      count[A[i]]++;
   }

   vector<int> result(N, 0);

   for (int i = 0; i < N; i++)
   {
      int j = 2;
      int countNonDivisors = N;

      while (j * j <= A[i])
      {
         if (A[i] % j == 0)
         {
            countNonDivisors -= count[j];
            if ((A[i] / j) != j)
               countNonDivisors -= count[A[i] / j];
         }
         j += 1;
      }
      countNonDivisors -= count[1]; 
      if (A[i] != 1)
         countNonDivisors -= count[A[i]]; 
      result[i] = countNonDivisors;
   }
   return result;
}

int main()
{
   int arr1[] = {2, 4};
   vector<int> vect1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
   vector<int> res1 = solution(vect1);
}
