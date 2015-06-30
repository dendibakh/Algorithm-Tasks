#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int solution(vector<int> &A) 
{
   int result = 0;
   int multiplier = 0;

   for (vector<int>::iterator iter = A.begin(); iter != A.end(); ++iter)
   {
      if (0 == *iter)
      {
         multiplier++;
      }
      else
      {
         result += multiplier;
         if (result > 1000000000)
            return -1;
      }
   }
   return result;
}

int main()
{
   int arr[] = {1, 1, 0, 1, 1, 0};
   vector<int> vect(arr, arr + 6);
   int result = solution(vect);
   //system("pause");
}