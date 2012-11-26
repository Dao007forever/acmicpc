#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 60 + 10, maxm = 75*75/2;

int n, h, m;
unsigned long long dp[maxm][maxn][maxn];

int main()
{
	freopen("in", "r", stdin);
	for (int i = 1; i < maxn; i++)
		dp[i][1][i] = 1;
	for (int i = 1; i < maxm; i++)
	for (int j = 1; j <= 60; j++)
	for (int k = 1; k <= maxn; k++)
	if (dp[i][j][k])
	{
		if (k - 1 && i + k - 1 < maxm)
			dp[i + k - 1][j + 1][k - 1] += dp[i][j][k];
		if (k + 1 < maxn && i + k + 1 < maxm)
			dp[i + k + 1][j + 1][k + 1] += dp[i][j][k];
	}
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d%d", &n, &h, &m);
		unsigned long long ret = 0;
		if (n >= maxm) n = maxm - 1;
		for (int i = 1; i <= n; i++)
			ret += dp[i][h][m];
		cout << ret << endl;
	}
	return 0;
}
