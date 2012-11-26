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

const int MAXN = 100 + 10;
const int inf = 1000000000;
int N, M, C;
int Map[MAXN][MAXN], dis[MAXN], vis[MAXN];

int calc(int u, int v)
{
	if (Map[u][v] > C) return inf;
	if (2 * Map[u][v] > C)
	{
		if (dis[v] + Map[u][v] <= C) return dis[v] + Map[u][v];
		else return inf;
	}
	if (Map[u][v] * 2 == C) return inf;

	int k = dis[v] + Map[u][v] - C, cnt;
	if (k < 0) k = 0;
	if (k % (C - 2 * Map[u][v]) == 0) cnt = k / (C - 2 * Map[u][v]);
	else cnt = k / (C - 2 * Map[u][v]) + 1;
	return dis[v] + (cnt * 2 + 1) * Map[u][v];
}

void solve()
{
	for (int i = 1; i <= N; i++)
		dis[i] = inf;
	memset(vis, 0, sizeof(vis));
	dis[N] = 0;
	for (int i = 1; i <= N; i++)
	{
		int k = -1;
		for (int j = 1; j <= N; j++)
			if (!vis[j] && (k == -1 || dis[j] < dis[k]))
				k = j;
		vis[k] = true;
		for (int j = 1; j <= N; j++)
			if (!vis[j])
			{
				int tmp = calc(j, k);
				if (tmp < dis[j]) dis[j] = tmp;
			}
	}
	if (dis[1] == inf) printf("-1\n");
	else printf("%d\n", dis[1]);
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d%d", &N, &M, &C);
		for (int i= 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				Map[i][j] = inf;
		for (int i = 1; i <= M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			scanf("%d", &Map[u][v]);
			Map[v][u] = Map[u][v];
		}

		solve();
	}
	return 0;
}
