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

const int MAXN = 1000 + 10;
int n;
int t[MAXN];

bool Check()
{
	stack<int> S;
	int pre;
	for (int i = 1; i < t[0]; i++)
		S.push(i);
	pre = t[0];
	for (int i = 1; i < n; i++)
	{
		if (t[i] > pre)
		{
			for (int j = pre + 1; j < t[i]; j++)
				S.push(j);
			pre = t[i];
		}
		else if (S.top() == t[i])
		{
			S.pop();
		}
		else return false;
	}
	return true;
}

int main()
{
	freopen("a", "r", stdin);
	while (cin >> n && n)
	{
		while (cin >> t[0] && t[0])
		{
			for (int i = 1; i < n; i++)
				cin >> t[i];
			if (Check()) cout << "Yes" << endl;
			else cout << "No" << endl;
		}
		cout << endl;
	}
	return 0;
}
