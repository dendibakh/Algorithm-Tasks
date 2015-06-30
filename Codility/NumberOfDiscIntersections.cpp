#include <algorithm>
#include <limits>
#include <stack>
#include <vector>
#include <functional>

using namespace std;

static const bool BEGIN = true;
static const bool END = false;

struct Point
{
    int coord;
    bool type;
};

bool compareFunction (const Point& first, const Point& second) 
{ 
    if (first.coord < second.coord)
       return true;
    else if (first.coord > second.coord)
       return false;
       
    if ((first.type == BEGIN) && (second.type == END))
       return true;
    return false; 
}

int solution(const vector<int> &A) 
{
    vector<Point> points;
	points.reserve(2*A.size());
    for (vector<int>::const_iterator iter = A.begin(); iter != A.end(); ++iter)
    {
        int center = iter - A.begin();
        int radius = *iter;
        Point p;
        p.coord = std::max(0, center - radius);
        p.type = BEGIN;
        points.push_back(p);
		if (std::numeric_limits<int>::max() - center - radius < 0)
            p.coord = std::numeric_limits<int>::max();
		else
			p.coord = center + radius;
        p.type = END;
        points.push_back(p);
    }
    std::sort(points.begin(), points.end(), std::ptr_fun(compareFunction));
    int result = 0;
    std::stack<int> st;
    for (vector<Point>::const_iterator iter = points.begin(); iter != points.end(); ++iter)
    {
        if (iter->type == BEGIN)
        {
            st.push(iter->coord);
        }    
        else 
        {
            st.pop();
            result += st.size();
			if (result > 10000000)
				return -1;
        }    
    }
    return result;
}

int main()
{
        int arr[] = {1, 5, 2, 1, 4, 0 };
        vector<int> vect(arr, arr + sizeof(arr) / sizeof(int));
        int res = solution(vect);
}
