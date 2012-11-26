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

const int MAXN = 750 + 10;
const int MAXM = 500000 + 10;
struct Edge
{
    int u, v, w;
}edge[MAXM], Mst[MAXM];
struct Point
{
	int x, y;
}ps[MAXN];
int N, M, num, tot;
int p[MAXN], rank[MAXN], g[MAXN][MAXN];

int dist(Point a, Point b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int find(int x)
{
    if (x != p[x])
        p[x] = find(p[x]);
    return p[x];
}

void Union(int x, int y)
{
    x = find(x); y = find(y);
    if (rank[x] > rank[y])
    {
        p[y] = x;
    }
    else
    {
        p[x] = y;
        if (rank[x] == rank[y]) rank[y]++;
    }
}

int cal()
{
    int res = 0;
    int u, v;
    for (int i = 1; i <= N; i++)
    {
        p[i] = i;
        rank[i] = 0;
    }
	scanf("%d", &M);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d%d", &u, &v);
		g[u][v] = 1;
		if (find(u) != find(v)) Union(u, v);
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = i + 1; j <= N; j++)
		{
			if (g[i][j])
			{
				g[i][j] = 0;
				continue;
			}
			edge[num].w = dist(ps[i], ps[j]);
			edge[num].u = i;
			edge[num++].v = j;
		}
	}
}

bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}

int Kruskal()
{
	sort(edge, edge + num, cmp);
    int u, v;
    for (int i = 0; i < num && tot < N - 1; i++)
    {
        u = edge[i].u;
        v = edge[i].v;
        if (find(u) != find(v))
        {
			Mst[tot++] = edge[i];
            Union(u, v);
        }
    }
	if (tot == 0) puts("No new highways need");
	else 
	{
		for (int i = 0; i < tot; i++)
			printf("%d %d\n", Mst[i].u, Mst[i].v);
	}
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		num = tot = 0;
		memset(g, 0, sizeof(g));
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			scanf("%d%d", &ps[i].x, &ps[i].y);
		}
		cal();
		Kruskal();
		if (Test) puts("");
	}
	return 0;
}
