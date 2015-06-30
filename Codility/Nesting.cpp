#include <algorithm>
#include <stack>
#include <string>

using namespace std;

int solution(const string &S) 
{
    stack<char> st;
    for (string::const_iterator iter = S.begin(); iter != S.end(); ++iter)
    {
        switch (*iter)
        {
            case '{':
            case '[':
            case '(':
                st.push(*iter);
                break;
            case '}':
                if (st.empty())
                   return 0;
                if (st.top() != '{')
                   return 0;
                st.pop();   
                break;
            case ']':
                if (st.empty())
                   return 0;
                if (st.top() != '[')
                   return 0;
                st.pop();
                break;   
            case ')':
                if (st.empty())
                   return 0;
                if (st.top() != '(')
                   return 0;
                st.pop();
                break;
            default:
                return 0;    
        }
    }
    if (st.empty())
       return 1;
    return 0;
}
