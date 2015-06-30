#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

vector<int> solution(string &S, vector<int> &P, vector<int> &Q) 
{
   int lenght = S.size();
   vector<int> A(lenght, 0);
   vector<int> C(lenght, 0);
   vector<int> G(lenght, 0);
   int index = 0;
   int lastA = 0;
   int lastC = 0;
   int lastG = 0;
   for (string::iterator iter = S.begin(); iter != S.end(); ++iter)
   {
      index = iter - S.begin();
      switch (*iter)
      {
      case 'A':
         lastA ++;
         break;
      case 'C':
         lastC ++;
         break;
      case 'G':
         lastG ++;
         break;
      case 'T':
         break;
      }
      A[index] = lastA;
      C[index] = lastC;
      G[index] = lastG;
   }
   vector<int> result(P.size(), 0);
   for (vector<int>::iterator iter = result.begin(); iter != result.end(); ++iter)
   {
      index = iter - result.begin();
      int first  = P[index];
      int second = Q[index];
      if (first == second)
      {
         switch (S[first])
         {
         case 'A':
            result[index] = 1;
            break;
         case 'C':
            result[index] = 2;
            break;
         case 'G':
            result[index] = 3;
            break;
         case 'T':
            result[index] = 4;
            break;
         }
      }
      else
      {
         int begin = (first > 0) ? first - 1 : 0;
         if (A[second] - A[begin] > 0)
            result[index] = 1;
         else if (C[second] - C[begin] > 0)
            result[index] = 2;
         else if (G[second] - G[begin] > 0)
            result[index] = 3;
         else
            result[index] = 4;
      }
   }
   return result;
}

int main()
{
   int arr1[] = {2, 4, 6, 1, 10, 10, 0};
   int arr2[] = {3, 7, 8, 10, 10, 13, 8};
   vector<int> result = solution(string("GGGAAAGGGGAAAAA"), vector<int>(arr1, arr1+7), vector<int>(arr2, arr2+7));
   //system("pause");
}