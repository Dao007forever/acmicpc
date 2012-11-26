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

int m, n;
int c[55];
long long dp[55][55];
long long cnt[55][55];

int main()
{
	freopen("a", "r", stdin);
	for (int i = 0; i <= 50; i++)
		cnt[i][0] = 1;
	for (int i = 1; i <= 50; i++)
		for (int j = 1; j <= i; j++)
			cnt[i][j] = cnt[i - 1][j - 1] + cnt[i - 1][j];
	while (scanf("%d%d", &m, &n) && (n || m))
	{
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++)
			scanf("%d", &c[i]);
		for (int i = 0; i <= n; i++)
			dp[i][0] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			{
				for (int k = 0; k <= j; k++)
					if (j - k <= c[i])
					dp[i][j] += dp[i - 1][k] * cnt[m - k][j - k];
			}
		cout << dp[n][m] << endl;
	}
	return 0;
}
