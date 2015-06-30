#include <vector>

using namespace std;

int solution(vector<int> &A) 
{
    const int N = static_cast<int>(A.size());
    std::vector<int> forward(N, 0);
    int maxSlize = 0;
    for (int i = 1; i < N; i++)
    {
       maxSlize = max(0, maxSlize + A[i]);
       forward[i] = maxSlize;
    }

    std::vector<int> backward(N, 0);
    maxSlize = 0;
    for (int i = N - 2; i >= 0; i--)
    {
       maxSlize = max(0, maxSlize + A[i]);
       backward[i] = maxSlize;
    }

    maxSlize = 0;
    for (int i = 0; i + 2 < N; i++)
    {
       maxSlize = max(maxSlize, forward[i] + backward[i+2]);
    }

    return maxSlize;
}

int main()
{
   int arr[] = {3, 2, 6, -1, 4, 5, -1, 2};
   vector<int> vect(arr, arr + sizeof(arr) / sizeof(arr[0]));
   int res = solution(vect);
}
