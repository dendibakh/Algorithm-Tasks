#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> &A) 
{
    std::sort(A.begin(), A.end());
    int max1 = 0;
    int first = *A.begin();
    int second = *(A.begin() + 1);
    int last = *(A.end() - 1);
    int preLast = *(A.end() - 2);
    int prePreLast = *(A.end() - 3);
    if ((first < 0) && (second < 0))
       max1 = first * second * last;
    int max2 = prePreLast * preLast * last;
    return (max2 > max1) ? max2 : max1;
}

int main()
{
        int arr[] = {-3, 1, 2, -2, 5, 6 };
        vector<int> vect(arr, arr + sizeof(arr) / sizeof(int));
        int res = solution(vect);
}
