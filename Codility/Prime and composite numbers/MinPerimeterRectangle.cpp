#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int solution(int N) 
{
   int i = 2;
   int maxDivisor = 1;
   while (i * i <= N)
   {
      if (N % i == 0)
         maxDivisor = i;
      i += 1;
   }
   int side1 = maxDivisor;
   int side2 = N/side1;
   return 2 * side1 + 2 * side2;
}

int main()
{
   int result = solution(30);
   //system("pause");
}