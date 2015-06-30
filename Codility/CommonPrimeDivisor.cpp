#include <vector>

using namespace std;

int gcd(int a, int b)
{
   int k = a % b;
   if (k == 0)
      return b;
   return gcd(b, k);
}

bool recursiveCheck(int gcdValue, int divisor)
{
   int newGCD = gcd(gcdValue, divisor);
   if (newGCD == 1)
      return false;
   if (divisor / newGCD == 1)
      return true;
   return recursiveCheck(newGCD, divisor / newGCD);
}

bool processDivisor(int divisor, int gcdValue)
{
   if (divisor < gcdValue)
   {
      if (gcdValue % divisor == 0)
         return true;
   }
   return recursiveCheck(gcdValue, divisor);
}

bool checkPair(int a, int b)
{
   if (a == b)
      return true;
   int gcdValue = gcd(a, b);
   if (gcdValue == 1)
      return false;
   return processDivisor( a / gcdValue, gcdValue ) && processDivisor ( b / gcdValue, gcdValue );
}

int solution(vector<int> &A, vector<int> &B) 
{
   const int N = static_cast<int>(A.size());
   int count = 0;
   for (int i = 0; i < N; i++)
   {
      if (checkPair(A[i], B[i]))
         count++;
   }
   return count;
}

int main()
{
   bool res1 = checkPair(15, 75);
   bool res2 = checkPair(10, 30);
   bool res3 = checkPair(9, 5);
   bool res4 = checkPair(4, 7);
   bool res5 = checkPair(5, 6);
   bool res6 = checkPair(2, 6);
   bool res7 = checkPair(2, 8);
   bool res8 = checkPair(3, 7);
   bool res9 = checkPair(12, 16);
   bool res10 = checkPair(15, 15*15*3);
   bool res11 = checkPair(15, 15*15*2);
   bool res12 = checkPair(1, 1);
   bool res13 = checkPair(15, 15*15*10);
   bool res18 = checkPair(15, 15*15*10);
   bool res14 = checkPair(1*2*3*4*5, 1*2*3*4*5);
   bool res15 = checkPair(1*2*3*4*5, 1*2*3*4*5*6);
   bool res16 = checkPair(1*2*3*4*5, 1*2*3*4*5*6*7);
   bool res17 = checkPair(1*2*3*4*5, 1*2*3*4*5*6*8);
   bool res19 = checkPair(1*2*3*4*5*9, 1*2*3*4*5*6*8);
   int arr1[] = {1};
   int arr2[] = {9};
   vector<int> vect1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
   vector<int> vect2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
   int res = solution(vect1, vect2);
}
