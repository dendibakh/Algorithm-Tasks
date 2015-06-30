#include <vector>

using namespace std;

int solution(const vector<int> &A) 
{
    const int N = static_cast<int>(A.size());
    if (N < 1)
       return -1;
    if (N == 1)
       return 0;
    vector<long long> left(N);
    vector<long long> right(N);
    left[0] = A[0];
    right[N - 1] = A[N - 1];
    for (int i = 1; i < N; i++) 
    {
       left[i] = left[i - 1] + A[i];
    }          
    for (int i = N - 2; i >= 0; i--) 
    {
       right[i] = right[i + 1] + A[i];
    }
    for (int i = 0; i < N; i++) 
    {
       if (left[i] == right[i])
          return i;
    }
    return -1;
}

int main()
{
   int arr[] = {-7, 1, 5, 2, -4, 3, 0};
   vector<int> vect(arr, arr + sizeof(arr) / sizeof(int));
   int res = solution(vect);
}