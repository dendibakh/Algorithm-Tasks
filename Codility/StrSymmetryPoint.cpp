#include <iostream>
#include <string>

using namespace std;

int solution(const string &S)
{
    size_t index = S.size();
    if (0 == index)
    	return -1;
    if (1 == index)
       	return 0;

    if (0 == index % 2)
    	return -1;

    size_t middle = index / 2;
    for (size_t i = 1; i <= middle; ++i)
    	if (S[middle - i] != S[middle + i])
    		return -1;

    return middle;
}

int main()
{
	int res1 = solution("racecar");
	int res4 = solution("racecat");
	int res2 = solution("");
	int res3 = solution("x");
	int r = res1 + res2 + res3 + res4;
	cout << r;
}
