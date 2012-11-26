#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m, p, a, b;
double map[33][33], dp[1 << 9][33], v[33];

void init()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			map[i][j] = 9e99;
	for (int i = 0; i < (1 << p); i++)
		for (int j = 1; j <= n; j++)
			dp[i][j] = 9e90;
	for (int i = 0; i < p; i++)
		scanf("%lf", &v[i]);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		scanf("%lf", &map[u][v]);
		map[v][u] = map[u][v];
	}
}

void solve()
{
	double ans = 9e99;
	dp[0][a] = 0;
	for (int i = 0; i < (1 << p); i++)
		for (int j = 1; j <= n; j++)
		if (dp[i][j] < 9e50)
		{
			for (int k = 0; k < p; k++)
			if ((i | (1 << k)) != i)
				for (int l = 1; l <= n; l++)
					if (dp[i][j] + map[j][l] / v[k] < dp[i | (1 << k)][l])
					{
						dp[i | (1 << k)][l] = dp[i][j] + map[j][l] / v[k];
					//	if (l == b) ans = min(ans, dp[i | (1 << k)][l]);
					}
		}
	for (int i = 0; i < (1 << p); i++)
		ans = min(ans, dp[i][b]);
	if (ans > 9e50) printf("Impossible\n");
	else printf("%.3lf\n", ans);
}

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d%d%d%d%d", &p, &n, &m, &a, &b) && n + m + p + a + b)
	{
		init();
		solve();
	}
	return 0;
}
