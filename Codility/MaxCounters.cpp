#include <vector>
#include <numeric>

using namespace std;

#include <algorithm>

class Counter
{
    public:
       Counter(vector<int>& count) : count(count) , base(0), max (0) , N(count.size()) {}
      ~Counter() 
      {
      }
       void operator() (int i) 
       {
           if (N + 1 == i)
           {
               base = max;
           }
         else
         {
            if (count[i-1] > base)
               count[i-1]++;
            else
               count[i-1] = base + 1;
            if (count[i-1] > max)
            {
               max = count[i-1];
            }
         }
       }
      vector<int> getResult()
      {
         for (vector<int>::iterator iter = count.begin(); iter != count.end(); ++iter)
            if (*iter < base)
               *iter = base;
         return count;
      }
    private:
      vector<int>& count;
       int base;
       int max;
       const int N;
};

vector<int> solution(int N, vector<int> &A) 
{
   vector<int> count (N, 0);
   Counter counter(count);
   Counter result = for_each (A.begin(), A.end(), counter);
   return result.getResult();
}

int main()
{
   int arr[] = {3, 4, 4, 6, 1, 4, 4};
   vector<int> vect(arr, arr + 7);
   vector<int> result = solution(5, vect);
   system("pause");
}

// Идея в том, что мы просто храним base - текущий максимальный счетчик. При этом постоянно увеличиваем каждый счетчик, прибавляя 1 к base.
// Потом проходимся по всему массиву и если < base, значит счетчик не инкрементировался.