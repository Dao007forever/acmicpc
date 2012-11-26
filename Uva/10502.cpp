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

int n, m;
char s[111][111];
int dp[111][111];

int solve()
{
	for (int j = 0; j < m; j++)
		dp[0][j] = s[0][j] == '1' ? 1 : 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			dp[i][j] = s[i][j] == '1' ? dp[i - 1][j] + 1 : 0;
		}

	int res = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int tmp = dp[i][j];
			for (int k = j; k < m; k++)
			{
				tmp = min(tmp, dp[i][k]);
				res += tmp;
			}
		}
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &n) && n)
	{
		scanf("%d", &m);
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
		cout << solve() << endl;
	}
	return 0;
}
