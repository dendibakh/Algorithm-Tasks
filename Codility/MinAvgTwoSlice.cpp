#include <vector>

using namespace std;

int solution(vector<int> &A) 
{
    int result = 0;
    vector<int>::const_iterator i = A.begin();
    vector<int>::const_iterator j = A.end();
    j--;
    while (j - i >= 0) 
    {
       int sum1 = result + *i;
       int sum2 = result - *j;
       if (abs(sum1) <= abs(sum2))
       {
          result += *i;
          i++;
       }
       else
       {
          result -= *j;
          j--;
       }
    } 	       
    return abs(result);
}

int main()
{
	int arr[] = {3, 1, 2, 4, 3};
	vector<int> vect(arr, arr + sizeof(arr) / sizeof(int));
	int res = solution(vect);
}