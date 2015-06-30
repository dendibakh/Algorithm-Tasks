#include <vector>
#include <algorithm>

using namespace std;

vector<int> Eratosphen(int N)
{
   vector<bool> marked(N + 1, true);
   for (int i = 2; i * i <= N; i++)
   {
      if (marked[i])
      {
         for (int k = i * i; k <= N; k+=i)
         {
            marked[k] = false;
         }
      }
   }

   vector<int> primes;
   for (int i = 2; i <= N; i++)
   {
      if (marked[i])
         primes.push_back(i);
   }
   return primes;
}

vector<int> calcSemiPrimes(const vector<int> &primes, int N)
{
   vector<int> semiPrimes;
   for (vector<int>::const_iterator i = primes.begin(); i != primes.end(); ++i)
   {
      for (vector<int>::const_iterator j = i; j != primes.end(); ++j)
      {
         int product = (*i) * (*j);
         if ((product <= N) && (product > 0))
            semiPrimes.push_back( (*i) * (*j) );
      }
   }
   std::sort(semiPrimes.begin(), semiPrimes.end());
   return semiPrimes;
}

vector<int> countSemiPrimes(const vector<int> &semiPrimes, int N)
{
   vector<int> countSemiPrimes(N + 1, 0);
   for (vector<int>::const_iterator i = semiPrimes.begin(); i != semiPrimes.end(); ++i)
   {
      countSemiPrimes[*i]++;
   }
   for (vector<int>::iterator i = countSemiPrimes.begin() + 1; i != countSemiPrimes.end(); ++i)
   {
      size_t index = i - countSemiPrimes.begin();
      countSemiPrimes[index] += countSemiPrimes[index - 1];
   }
   return countSemiPrimes;
}

vector<int> processQuerries(const vector<int> &P, const vector<int> &Q, const vector<int> &countSP)
{
   size_t size = P.size();
   vector<int> result(size, 0);
   for (size_t i = 0; i < size; i++)
   {
      result[i] = countSP[Q[i]] - countSP[P[i] - 1];
   }
   return result;
}

vector<int> solution(int N, const vector<int> &P, const vector<int> &Q) 
{
   vector<int> primes = Eratosphen(N);
   vector<int> semiPrimes = calcSemiPrimes(primes, N);
   vector<int> countSP = countSemiPrimes(semiPrimes, N);
   return processQuerries(P, Q, countSP);
}

int main()
{
   int arrP[] = {1, 4, 16};
   int arrQ[] = {30000, 10, 20};
   vector<int> P(arrP, arrP + sizeof(arrP) / sizeof(arrP[0]));
   vector<int> Q(arrQ, arrQ + sizeof(arrQ) / sizeof(arrQ[0]));
   vector<int> res1 = solution(50000, P, Q);
}
