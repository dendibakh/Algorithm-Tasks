#include <vector>

using namespace std;

int solution(vector<int>& A) 
{
   const int N = static_cast<int>(A.size());
   unsigned int countHits = 0;
   vector<bool> count(N, false);
   for (int i = 0; i < N; i++)
   {
      if (!count[A[i]])
      {
         countHits++;
         count[A[i]] = true;
      }
   }
   for (int i = 0; i < N; i++)
   {
      if (count[A[i]])
      {
         count[A[i]] = false;
         countHits--;
         if (countHits == 0)
            return i; 
         
      }
   }
   return 0;
}

int main()
{
   int arr[] = {2, 2, 1, 0, 1};
   size_t sizeArr = sizeof(arr) / sizeof(arr[0]);
   vector<int> vect(arr, arr + sizeArr);
   int res = solution(vect);
}
