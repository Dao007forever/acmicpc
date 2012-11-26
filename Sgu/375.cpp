#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long n;

int main()
{
	freopen("a", "r", stdin);
	cin >> n;
	if (n % 2 == 0) 
	{
		cout << "No solution" << endl;
		return 0;
	}
	stack<int> S;
	while (n > 1)
	{
		int temp = (n + 1) / 2;
		if (temp % 2 == 0) 
		{
			S.push(2);
			n = (n - 1) / 2;;
		}
		else 
		{
			S.push(1);
			n = temp;
		}
	}
	cout << S.size() << endl;
	while (!S.empty())
	{
		int t = S.top();
		S.pop();
		cout << t << " ";
	}
	cout << endl;
	return 0;
}
