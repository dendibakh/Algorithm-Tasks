#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> &A)
{
	int answer = 0;
	for (vector<int>::iterator i = A.begin(); i != A.end(); ++i)
		answer ^= *i;
	return abs(answer);
}

int main()
{
	//int arr[] = {9, 3, 9, 3, 9, 7, 9};
	int arr[] = {4, 7, 9, 42, 9, 7, 4};
	vector<int> vect(arr, arr + sizeof(arr) / sizeof(arr[0]));
	int res1 = solution(vect);
	cout << res1;
}
