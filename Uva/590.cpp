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

const int inf = 100000000;
int cost[11][11][111], day[11][11];
int dp[1111][11];
int N, K;

int main()
{
	freopen("a", "r", stdin);
	int cas = 1;
	while (scanf("%d%d", &N, &K))
	{
		if (N == 0 && K == 0) break;
		printf("Scenario #%d\n", cas++);
		if (N == 0 && K == 0) break;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
			if (i != j)
			{
				int num;
				scanf("%d", &num);
				day[i][j] = num;
				for (int k = 0; k < num; k++)
					scanf("%d", &cost[i][j][k]);
			}

		memset(dp, -1, sizeof(dp));
		dp[0][1] = 0;
		for (int k = 1; k <= K; k++)
		{
			for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
			if (i != j)
			{
				if (dp[k - 1][j] == -1) continue;
				int t = (k - 1) % day[j][i];
				if (cost[j][i][t] > 0)
				{
					if (dp[k][i] == -1 || dp[k - 1][j] + cost[j][i][t] < dp[k][i])
					{
						dp[k][i] = dp[k - 1][j] + cost[j][i][t];
					}
				}
			}
		}
		if (dp[K][N] == -1) printf("No flight possible.\n");
		else printf("The best flight costs %d.\n", dp[K][N]);
		printf("\n");
	}
	return 0;
}
