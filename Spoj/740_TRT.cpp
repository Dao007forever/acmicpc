#include <cstdio>
#include <iostream>
using namespace std;

int n;
int a[2222];
int dp[2222][2222];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
	{
		dp[i][0] = dp[i - 1][0] + i * a[i];
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			dp[i][j] = max(dp[i - 1][j - 1] + i * a[n - j + 1], dp[i - 1][j] + i * a[i - j]);
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, dp[n][i]);
	printf("%d\n", ans);
	return 0;
}
