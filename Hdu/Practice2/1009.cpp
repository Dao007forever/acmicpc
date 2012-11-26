#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 110;
int N, M, L;
int t[MAXN], v[MAXN];
int dp[MAXN][1010];

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d", &N, &M, &L);
		for (int i = 1; i <= N; i++)
			scanf("%d%d", &t[i], &v[i]);
		memset(dp, -1, sizeof(dp));
		dp[0][0] = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = M; j >= 1; j--)
			{
				for (int l = L; l >= t[i]; l--)
				if (dp[j - 1][l - t[i]] != -1)
					dp[j][l] = max(dp[j][l], dp[j - 1][l - t[i]] + v[i]);
			}
		}
		int res = 0;
		for (int i = 1; i <= L; i++)
			res = max(res, dp[M][i]);
		printf("%d\n", res);
	}
	return 0;
}
