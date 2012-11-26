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

const int MAXT = 250 + 10;
const int MAXN = 100 + 10;
int N, T;
int Time[MAXN][MAXN], Risk[MAXN][MAXN];
int dp[MAXT][MAXN];

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &N, &T);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				scanf("%d", &Time[i][j]);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				scanf("%d", &Risk[i][j]);
		memset(dp, -1, sizeof(dp));
		dp[0][1] = 0;
		for (int i = 0; i < T; i++)
			for (int j = 1; j <= N; j++)
			if (dp[i][j] != -1)
				for (int k = 1; k <= N; k++)
				if (j != k && i + Time[j][k] <= T && (dp[i + Time[j][k]][k] == -1 || dp[i][j] + Risk[j][k] < dp[i + Time[j][k]][k]))
					dp[i + Time[j][k]][k] = dp[i][j] + Risk[j][k];
		int k = -1, ans = -1;
		for (int i = 0; i <= T; i++)
			if (dp[i][N] != -1 && (ans == -1 || dp[i][N] < ans))
			{
				ans = dp[i][N];
				k = i;
			}
		if (ans == -1) printf("-1\n");
		else printf("%d %d\n", ans, k);
	}
	return 0;
}
