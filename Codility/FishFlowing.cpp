#include <algorithm>
#include <stack>
#include <string>
#include <vector>

using namespace std;

static const int UP_STREAM = 0;
static const int DOWN_STREAM = 1;

int solution(vector<int> &A, vector<int> &B) 
{
    std::stack<int> downStream;
    std::stack<int> upStream;
    const int N = A.size();
    int result = 0;
    for (int i = 0; i < N; i++)
    {
       int currentSize = A[i];
       int currentDirection = B[i];
       if ((i == 0) && (currentDirection == UP_STREAM))
       {
          result++;
          continue;
       }
       if ((i == N - 1) && (currentDirection == DOWN_STREAM))
       {
          result++;
          continue;
       }
       if (UP_STREAM == currentDirection)
       {
          if (downStream.empty())
          {
             upStream.push(currentSize);
          }
          else
          {
             while (true)
             {
                int oppositeFishSize = downStream.top();
                if (currentSize < oppositeFishSize)
                   break;
                else
                {
                   downStream.pop();
                   if (downStream.empty())
                   {
                      upStream.push(currentSize);
                      break;
                   }   
                }
             }
          }
       }
       else
       {
          downStream.push(currentSize);
       }
    }
    result += downStream.size() + upStream.size();
    return result;
}

int main()
{
   int arr_sizes[] = {4, 3, 2, 1, 5};
   int arr_directions[] = {0, 1, 0, 0, 0};
   vector<int> sizes(arr_sizes, arr_sizes + sizeof(arr_sizes) / sizeof(arr_sizes[0]));
   vector<int> directions(arr_directions, arr_directions + sizeof(arr_directions) / sizeof(arr_directions[0]));
   int res = solution(sizes, directions);
}
