#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// Очень странно работает система тестов для этого задания. Поэтому до конца отладить не удалось. Основной тест проходит.

int solution(vector<int> &A) 
{
    const int N = static_cast<int>(A.size());
    
    if (N < 4)
       return 0;

    std::vector<int> divisors;
    int i = 2;
    while (i * i <= N)
    {
       if (N % i == 0)
          divisors.push_back(i);
       i += 1;
    }
    if (0 == divisors.size())
       return 0;

    std::vector<int> peeks;
    int peekCount = 0;
    for (int i = 1; i < N - 1; i++)
    {
       if ( (A[i] > A[i - 1]) && (A[i] > A[i + 1]) )
       {
          peeks.push_back(i);
          peekCount++;
       }
    }
    if ( peekCount < 2 )
      return 0;

    const int divisorsCount = static_cast<int>(divisors.size());
    std::vector<int> allDivisors;
    for (int i = 0; i < divisorsCount; i++)
    {
       allDivisors.push_back(divisors[i]);
       allDivisors.push_back(N / divisors[i]);
    }

    sort(allDivisors.begin(), allDivisors.end(), greater<int>());

    for (std::vector<int>::iterator i = allDivisors.begin(); i != allDivisors.end(); ++i)
    {
       bool match = true;
       int elemsInBlock = N / *i;
       for (std::vector<int>::iterator j = peeks.begin(); j != peeks.end(); ++j)
       {
          int k = static_cast<int>(j - peeks.begin());
          if (*j / elemsInBlock != k)
          {
             match = false;
             break;
          }
       }
       if (match)
          return *i;
    }

    return 1;
}

int main()
{
   int arr[] = {1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2};
   int arr1[] = {3,4,3};
   vector<int> vect(arr, arr + sizeof(arr) / sizeof(arr[0]));
   int res = solution(vect);
   vector<int> vect1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
   int res1 = solution(vect1);
}
