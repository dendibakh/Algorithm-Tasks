#include <vector>
#include <algorithm>
#include <set>

using namespace std;

//Это решение за N^2. Нужно решить за N * log N. Решение http://codesays.com/2014/solution-to-array-inversion-count-by-codility/

bool All (int i) 
{ 
   return true; 
}

int solution(const vector<int> &A) 
{
    const int N = static_cast<int>(A.size());
    int count = 0;
    std::multiset<int> m;
    for (int i = N - 1; i >= 0; --i)
    {
       std::multiset<int>::iterator j = m.insert(A[i]);
       std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> bounds = std::equal_range (m.begin(), j, A[i]);
       count += std::count_if(m.begin(), j, All) - std::count_if(bounds.first, bounds.second, All);
    }

    return count;
}

int main()
{
   int a[] = {-1, 6, 3, 4, 7, 4};
   size_t sizeA = sizeof(a) / sizeof(a[0]);
   vector<int> A(a, a + sizeA);
   int res = solution(A);
}
