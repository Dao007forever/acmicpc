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

const int inf = 2000000000;
int dp[111][222];
int dis[111], cost[111];

int main()
{
	freopen("a", "r", stdin);
	int Test, len;
		scanf("%d", &len);
		int n = 1;
		while (scanf("%d%d", &dis[n], &cost[n]) != EOF)
		{
			n++;
		}
		memset(dp, -1, sizeof(dp));
		dp[0][100] = 0;
		for (int i = 1; i < n; i++)
		{
			int t = dis[i] - dis[i - 1];
			for (int j = 0; j <= 200; j++)
				if (dp[i - 1][j] != -1 && j - t >= 0)
					dp[i][j - t] = dp[i - 1][j];
			for (int j = 1; j <= 200; j++)
				if (dp[i][j - 1] != -1 && (dp[i][j] == -1 || dp[i][j - 1] + cost[i] < dp[i][j]))
					dp[i][j] = dp[i][j - 1] + cost[i];
		}
		int ans = -1;
		for (int i = 100 + len - dis[--n]; i <= 200; i++)
		if (dp[n][i] != -1 && (ans == -1 || dp[n][i] < ans))
			ans = dp[n][i];
		if (ans == -1) printf("Impossible\n");
		else printf("%d\n", ans);
	return 0;
}


