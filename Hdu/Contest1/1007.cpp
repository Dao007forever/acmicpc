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

const int MAXN = 800 + 10;
const double inf = 1e10;
struct Edge
{
	int v, next;
	double w;
}edge[MAXN * MAXN];
int N, M, L, U, num, cnt;
int x[MAXN][MAXN], vis[MAXN], Head[MAXN];
double dis[MAXN];

void addEdge(int u, int v, double w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void build()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			double tmpL = (double)L / x[i][j];
			double tmpR = (double)U / x[i][j];
			addEdge(i, N + j, -log(tmpL));
			addEdge(N + j, i, log(tmpR));
		}
	}
}

bool spfa()
{
	for (int i = 1; i <= N + M; i++)
		dis[i] = inf;
	dis[1] = 0.0;
	memset(vis, 0, sizeof(vis));
	vis[1] = true;
	queue<int> Q;
	Q.push(1);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int i = Head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].v;
			if (dis[u] + edge[i].w < dis[v])
			{
				dis[v] = dis[u] + edge[i].w;
				if (!vis[v])
				{
					vis[v] = true;
					Q.push(v);
					cnt++;
					if (cnt > 2 * (N + M)) return false;
				}
			}
		}
		vis[u] = false;
	}
	/*for (int i = 1; i <= N + M; i++)
	{
		int ans = (int)pow(10.0, dis[i]);
		printf("%d\n", ans);
	}*/
	return true;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d%d%d", &N, &M, &L, &U) != EOF)
	{
		num = 0;
		memset(Head, -1, sizeof(Head));
		cnt = 0;
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &x[i][j]);

		build();
		if (spfa()) puts("YES");
		else puts("NO");
	}
	return 0;
}
