#include <vector>
#include <stack>

using namespace std;

int solution(vector<int> &A) 
{
   std::stack<int> st;
   for (vector<int>::const_iterator iter = A.begin(); iter != A.end(); ++iter)
   {
      if (st.empty())
      {
         st.push(*iter);
      }
      else
      {
         if (st.top() == *iter)
            st.push(*iter);   
         else
            st.pop();   
      }
   }
   if (st.empty())
      return -1;

   int candidate = st.top();
   unsigned int count = 0;
   int dominatorPosition = 0;
   for (vector<int>::const_iterator iter = A.begin(); iter != A.end(); ++iter)
   {
      if (candidate == *iter)
      {
         if (!dominatorPosition)
            dominatorPosition = static_cast<int>(iter - A.begin());
         count++;
      }
   }
   if (count > A.size() / 2)
      return dominatorPosition;

   return -1;
}

int main()
{
   int arr[] = {2, 4, 6, 1, 10, 10, 0};
   int result = solution(vector<int>(arr, arr + sizeof(arr) / sizeof(arr[0])));
   //system("pause");
}