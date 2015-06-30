#include <list>

using namespace std;

list<int> getBinary(int N)
{
   list<int> vect;
   int k = 0;
   int val = N;
   while (true)
   {
      k = val / 2;
      vect.push_front(val - k * 2);
      val = k;
      if (k == 0)
         break;
   }
   return vect;
}          

int solution(int N) 
{
   list<int> bin = getBinary(N);
   int maxGap = 0;
   int count = 0;
   for (list<int>::iterator i = bin.begin(); i != bin.end(); ++i)
   {
      if (*i == 0)
         count++;
      else if (*i == 1)
      {
         if (count > 0)
         {
            maxGap = max(maxGap, count);
            count = 0;
         }
      }
   }
   return maxGap;
}

int main()
{
   int res1 = solution(9);
   int res2 = solution(529);
   int res3 = solution(20);
   int res4 = solution(15);
   int res5 = solution(1041);
}
