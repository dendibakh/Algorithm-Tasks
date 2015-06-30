int gcd(int a, int b)
{
   if (a % b == 0)
      return b;
   return gcd(b, a % b);
}     

int solution(int N, int M) 
{
   int k = gcd(N, M);
   return N / k;
}

int main()
{
   int res1 = solution(10, 2);
   int res2 = solution(10, 3);
   int res3 = solution(10, 6);
   int res4 = solution(11, 5);
}
