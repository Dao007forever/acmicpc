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

char str[15];
int tot;
long long num[10000];

void dfs(long long n, int n4, int n7)
{
	if ((n4 + n7) % 2 == 0 && n4 == n7 && n4 > 0 && n7 > 0)
	{
		num[++tot] = n;
	}
	if (n4 + n7 < 10)
	{
		dfs(n * 10 + 4, n4 + 1, n7);
		dfs(n * 10 + 7, n4, n7 + 1);
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", str);
	tot = 0;
	int n = strlen(str);
	dfs(0, 0, 0);
	sort(num + 1, num + tot + 1);
	int temp = atoi(str);
	for (int i = 1; i <= tot; i++)
	{
		if (num[i] >= temp)
		{
			cout << num[i] << endl;
			break;
		}
	}
	return 0;
}
