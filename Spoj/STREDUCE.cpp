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

const int MAXN = 300 + 10;
const int Inf = 500;
int N;
char str[MAXN];
int dp[MAXN][MAXN];
char c[MAXN][MAXN];

int dfs(int l, int r)
{
	int res = 300;
	if (dp[l][r]) return dp[l][r];
	if (r < l) return 0;
	if (l == r)
	{
		dp[l][r] = 1;
		c[l][r] = str[l];
		return 1;
	}
	if (l + 1 == r)
	{
		dp[l][r] = 2;
		return 2;
	}
	if (l + 2 == r)
	{
		if (str[l] == str[r])
		{
			dp[l][r] = 1;
			c[l][r] = str[l + 1];
			return 1;
		}
		else 
		{
			dp[l][r] = 3;
			return 3;
		}
	}
	if (str[l] == str[r] && dfs(l + 1, r - 1) == 1)
	{
		dp[l][r] = 1;
		c[l][r] = c[l + 1][r - 1];
		return 1;
	}
	int cur;
	for (int i = l; i <= r - 1; i++)
	{
		int a = dfs(l, i), b = dfs(i + 2, r);
		cur = a + b + 1;
		if (a == 1 && b == 1 && c[l][i] == c[i + 2][r])
		{
			dp[l][r] = 1;
			c[l][r] = str[i + 1];
			return 1;
		}
		else if (cur < res)
			res = cur;
	}
	cur = dfs(l + 1, r) + 1;
	res = min(cur, res);
	cur = dfs(l, r - 1) + 1;
	res = min(cur, res);
	dp[l][r] = res;
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	memset(dp, 0, sizeof(dp));
	scanf("%s", str);
	N = strlen(str);
	cout << dfs(0, N - 1) << endl;
}
