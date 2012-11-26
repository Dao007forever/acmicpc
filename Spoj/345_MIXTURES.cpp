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

const int MAXN = 100 + 10;
const int inf = 2147483647;
int N;
int data[MAXN], sum[MAXN], dp[MAXN][MAXN];

int Calc(int i, int j)
{
	return (sum[j] - sum[i - 1]) % 100;
}

int dfs(int l, int r)
{
	if (l == r) return 0;
	if (dp[l][r] >= 0) return dp[l][r];

	dp[l][r] = inf;
	for (int k = l; k < r; k++)
		if (dfs(l, k) + dfs(k + 1, r) + Calc(l, k) * Calc(k + 1, r) < dp[l][r])
			dp[l][r] = dfs(l, k) + dfs(k + 1, r) + Calc(l, k) * Calc(k + 1, r);
	return dp[l][r];
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) != EOF)
	{
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &data[i]);
			sum[i] = sum[i - 1] + data[i];
		}
		memset(dp, -1, sizeof(dp));
		int ans = dfs(1, N);
		printf("%d\n", ans);
	}
	return 0;
}
