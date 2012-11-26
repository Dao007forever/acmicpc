#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int inf = 100000000;
int n;
int map[15][15];
int dp[1 << 15][15];

void init()
{
	n++;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			if (i != j && i != k && j != k)
				map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
}

void solve()
{
	memset(dp, -1, sizeof(dp));
	dp[1][0] = 0;
	for (int i = 1; i < (1 << n); i++)
		for (int j = 0; j < n; j++)
		{
			if (dp[i][j] == -1) continue;
			for (int k = 1; k < n; k++)
			if (!(i & (1 << k)))
			{
				if (dp[i | (1 << k)][k] == -1) dp[i | (1 << k)][k] = dp[i][j] + map[j][k];
				else dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + map[j][k]);
			}
		}
	int ans = inf;
	for (int i = 1; i < n; i++)
	if (dp[(1 << n) - 1][i] > 0)
		ans = min(ans, dp[(1 << n) - 1][i] + map[i][0]);
	printf("%d\n", ans);
}

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d", &n) && n)
	{
		init();
		solve();
	}
	return 0;
}
