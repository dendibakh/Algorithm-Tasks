#include <vector>
#include <numeric>

using namespace std;

int solution(int X, vector<int> &A)
{
    int positions = X;
    int k = -1;
    int* count = new int[X];
    for (int i = 0; i < X; i++)
       count[i] = 0;
    for (vector<int>::iterator iter = A.begin(); iter != A.end(); ++iter)
    {
        int numb = *iter;
        if (numb <= X)
        {
           if (!count[numb-1])
           {
               count[numb-1]++;
               positions--;
               if (!positions)
               {
                  k = iter - A.begin();
                  break;
               }  
           }
        }   
    }
    delete[] count;
    return k;
}

int main()
{
   int arr[] = {1, 3, 1, 4, 2, 3, 5, 4};
   vector<int> vect(arr, arr + 8);
   int result = solution(5, vect);
   system("pause");
}