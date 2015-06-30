#include <vector>
#include <numeric>

using namespace std;

int solution(vector<int> &A) 
{
    int N = A.size();
    int* count = new int[N];
    for (int i = 0; i < N; i++)
       count[i] = 0;
    bool permutation = true;
    for (vector<int>::iterator iter = A.begin(); iter != A.end(); ++iter)
    {
        int numb = *iter;
        if (numb > N)
        {
           permutation = false;
           break;
        }   
        if (!count[*iter-1])
        {
           count[*iter-1]++;
        }   
        else
        {
           permutation = false;
           break;
        }
    }
    if (permutation)
    {
       for (int i = 0; i < N; i++)
       {
           if (!count[i])
           {
               permutation = false;
               break;
           }
       }
    }
    delete[] count;
    return permutation ? 1 : 0;
}

int main()
{
   int arr[] = {4, 1, 3, 10};
   vector<int> vect(arr, arr + 4);
   int result = solution(vect);
   system("pause");
}