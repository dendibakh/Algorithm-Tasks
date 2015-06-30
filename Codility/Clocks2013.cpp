#include <vector>
#include <algorithm>

using namespace std;

void sortClocks(vector< vector<int> > &A)
{
   for (vector<vector<int> >::iterator i = A.begin(); i != A.end(); ++i)
   {
      sort(i->begin(), i->end());
   }
}

vector<vector<int> > getDifference(vector< vector<int> > &A, int P)
{
   vector<vector<int> > diff;
   for (vector<vector<int> >::iterator i = A.begin(); i != A.end(); ++i)
   {
      vector<int> curDiff;
      for (vector<int>::iterator j = i->begin() + 1; j != i->end(); ++j)
      {
         curDiff.push_back(*j - *(j - 1));
      }
      curDiff.push_back(P - *(i->end() - 1) + *(i->begin()) );
      sort(curDiff.begin(), curDiff.end());
      diff.push_back(curDiff);
   }
   return diff;
}

bool compareFunc(const vector<int> &left, const vector<int> &right) 
{ 
   const int N = static_cast<int>(left.size());
   for (int i = 0; i < N; i++)
   {
      if (right[i] == left[i])
         continue;
      if (right[i] > left[i])
         return true;
      return false;
   }
   return false;
}

void sortDifference(vector< vector<int> > &diff)
{
   sort(diff.begin(), diff.end(), compareFunc);
}

int countPairs(vector< vector<int> > &diff)
{
   int count = 0;
   int countEquals = 1;
   for (vector<vector<int> >::iterator i = diff.begin() + 1; i != diff.end(); ++i)
   {
      if (equal(i->begin(), i->end(), (i - 1)->begin() ))
      {
         countEquals++;
      }
      else
      {
         count+= (countEquals * ( countEquals - 1 ) ) / 2;
         countEquals = 1;
      }
   }
   count+= (countEquals * ( countEquals - 1 ) ) / 2;
   return count;
}

int solution(const vector< vector<int> > &A, int P)
{
   vector< vector<int> > &notConstA = const_cast<vector< vector<int> > &> (A);
   sortClocks(notConstA);
   vector<vector<int> > diff = getDifference(notConstA, P);
   sortDifference(diff);
   return countPairs(diff);
}

int main()
{
   int arr1[] = {1, 4, 3, 6};
   int arr2[] = {12, 2, 4, 6};
   int arr3[] = {12, 2, 3, 5};
   int arr4[] = {9, 11, 12, 2};
   int arr5[] = {1, 3, 6, 9};
   int arr6[] = {9, 11, 12, 2};
   int arr7[] = {9, 11, 12, 2};
   int arr8[] = {9, 11, 12, 2};
   int arr9[] = {9, 11, 12, 2};
   int arr10[] = {9, 11, 12, 2};      
   int arr11[] = {9, 11, 12, 2};
   int arr12[] = {9, 11, 12, 2};
   int arr13[] = {9, 11, 12, 2};
   int arr14[] = {9, 11, 12, 2};
   int arr15[] = {9, 11, 12, 2};

   size_t size = sizeof(arr1) / sizeof(arr1[0]);
   vector<int> vect1(arr1, arr1 + size);
   vector<int> vect2(arr2, arr2 + size);
   vector<int> vect3(arr3, arr3 + size);
   vector<int> vect4(arr4, arr4 + size);
   vector<int> vect5(arr5, arr5 + size);

   vector<int> vect6(arr6, arr6 + size);
   vector<int> vect7(arr7, arr7 + size);
   vector<int> vect8(arr8, arr8 + size);
   vector<int> vect9(arr9, arr9 + size);
   vector<int> vect10(arr10, arr10 + size);
   vector<int> vect11(arr11, arr11 + size);
   vector<int> vect12(arr12, arr12 + size);
   vector<int> vect13(arr13, arr13 + size);
   vector<int> vect14(arr14, arr14 + size);
   vector<int> vect15(arr15, arr15 + size);

   //vector<int> arr[] = {vect1, vect2, vect3, vect4, vect5, vect6, vect7, vect8, vect9, vect10, vect11, vect12, vect13, vect14, vect15};
   vector<int> arr[] = {vect1, vect3};
   size_t sizeClocks = sizeof(arr) / sizeof(arr[0]);
   vector<vector<int> > vect(arr, arr + sizeClocks);
   int res = solution(vect, 12);
}
