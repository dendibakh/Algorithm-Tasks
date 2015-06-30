#include <vector>
#include <limits>

using namespace std;

vector<int> getMinElements(const vector<int> &A)
{
   size_t size = A.size();
   vector<int> minElements(size, 0);
   int minElement = numeric_limits<int>::max();
   for(vector<int>::const_iterator iter = A.begin(); iter != A.end(); ++iter)
   {
      size_t index = iter - A.begin();
      minElement = min(minElement, *iter);
      minElements[index] = minElement;
   }
   return minElements;
}

int countDisks(const vector<int> &minElements, const vector<int> &B)
{
   int count = 0;
   int N = static_cast<int>(minElements.size());
   int M = static_cast<int>(B.size());
   for (int i = N - 1, j = 0; i >= 0; i--)
   {
      if (minElements[i] >= B[j])
      {
         count++;
         j++;
         if (j == M)
            break;
      }
   }
   return count;
}

int solution(vector<int> &A, vector<int> &B) 
{
   vector<int> minElements = getMinElements(A);
   return countDisks(minElements, B);
}

int main()
{
   int a[] = {5, 6, 4, 3, 6, 2, 3};
   int b[] = {2, 3, 5, 2, 4};
   size_t sizeA = sizeof(a) / sizeof(a[0]);
   size_t sizeB = sizeof(b) / sizeof(b[0]);
   vector<int> A(a, a + sizeA);
   vector<int> B(b, b + sizeB);
   int res = solution(A, B);
}
