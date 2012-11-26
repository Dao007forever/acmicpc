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
int n, T;
int dis[55];
int t[55][55], g[55][55];
int cost[55][1111], vis[55][1111];

void Dijkstra()
{
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= T; j++)
			cost[i][j] = inf;
	memset(vis, 0, sizeof(vis));
	cost[1][0] = 0;
	vis[1][0] = true;
	queue<int> Q, C;
	Q.push(1);
	C.push(0);
	while (!Q.empty())
	{
		int now = Q.front(), k = C.front();
		Q.pop(); C.pop();
		for (int i = 1; i <= n; i++)
			if (i != now)
			{
				int tmp = k + t[now][i];
				if (tmp <= T && cost[now][k] + g[now][i] < cost[i][tmp])
				{
					cost[i][tmp] = cost[now][k] + g[now][i];
					if (!vis[i][tmp])
					{
						vis[i][tmp] = true;
						Q.push(i);
						C.push(tmp);
					}
				}
			}
		vis[now][k] = false;
	}
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &n, &T) && (n || T))
	{
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &t[i][j]);
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &g[i][j]);

		Dijkstra();
		int Mincost = inf, Mintime = inf;
		for (int i = 0; i <= T; i++)
			if (cost[n][i] < Mincost)
			{
				Mincost = cost[n][i];
				Mintime = i;
			}
		printf("%d %d\n", Mincost, Mintime);
	}
	return 0;
}
