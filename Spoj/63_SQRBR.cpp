#include <cstdio>
#include <cstring>

const int MAXN = 111;
int n, k;
int flag[MAXN], dp[MAXN][MAXN];

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		memset(flag, 0, sizeof(flag));
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= k; i++)
		{
			int x;
			scanf("%d", &x);
			flag[x] = 1;
		}

		memset(dp, 0, sizeof(dp));
		dp[1][0] = 1;
		for (int i = 1; i <= n + n; i++)
		{
			for (int j = 0; j <= n; j++)
			{
				dp[i + 1][j + 1] += dp[i][j];
				if (!flag[i] && j)
				{
					dp[i + 1][j - 1] += dp[i][j];
				}
			}
		}
		printf("%d\n", dp[n + n + 1][0]);
	}
	return 0;
}
