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

const int MAXN = 200 + 10;
struct Point
{
	double x, y;
}P[MAXN], S, E;
int N;
double v1, v2, g[MAXN][MAXN], dis[MAXN];
int vis[MAXN][MAXN], pre[MAXN][5], d[MAXN], p[MAXN], res[MAXN];

double dist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%lf%lf", &v1, &v2);
	scanf("%d", &N);
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= N; i++)
	{
		scanf("%lf%lf", &P[i].x, &P[i].y);
	}
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
		g[i][j] = g[j][i] = dist(P[i], P[j]) / v1;
	int u, v;
	while (scanf("%d%d", &u, &v))
	{
		if (u == 0 && v == 0) break;
		g[u][v] = g[v][u] = dist(P[u], P[v]) / v2;
		vis[u][v] = vis[v][u] = 1;
	}
	scanf("%lf%lf", &S.x, &S.y);
	scanf("%lf%lf", &E.x, &E.y);
	double ans = dist(S, E) / v1;
	queue<int> Q;
	for (int i = 1; i <= N; i++)
	{
		Q.push(i);
		dis[i] = dist(S, P[i]) / v1;
		p[i] = true;
	}
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int v = 1; v <= N + 1; v++)
		{
			if (dis[u] + g[u][v] < dis[v])
			{
				dis[v] = dis[u] + g[u][v];
				pre[v][0] = u;
				pre[v][1] = vis[u][v];
				if (!p[v])
				{
					p[v] = true;
					Q.push(v);
				}
			}
		}
		p[u] = false;
	}
	int k = 0;
	for (int i = 1; i <= N; i++)
	{
		if (dis[i] + dist(P[i], E) / v1 < ans)
		{
			ans = dis[i] + dist(P[i], E) / v1;
			k = i;
		}
	}
	printf("%.7lf\n", ans);
	int tot = 0;
	while (k != 0)
	{
		tot++;
		d[tot] = k;
		k = pre[k][0];
	}
	int m = 0;
	for (int i = 1; i <= tot; i++)
	{
		if (pre[d[i]][1])
		{
			if (m == 0 || res[m] != d[i])
			{
				m++;
				res[m] = d[i];
			}
			m++;
			res[m] = d[i + 1];
		}
	}
	printf("%d", m);
	for (int i = m; i >= 1; i--)
		printf(" %d", res[i]);
	return 0;
}
