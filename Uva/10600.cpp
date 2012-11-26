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

const int MAXN = 500 + 10;
const int MAXM = 250000 + 10;
const int inf = 0x3f3f3f3f;
struct Edge
{
	int u, v, w;
	int next;
	int use, can;
}edge[2 * MAXM];
int N, M, num;
int Head[MAXN], p[MAXN], Rank[MAXN];

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].u = u;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

bool cmp(Edge a, Edge b)
{
	return a.w < b.w;
}

int Find(int x)
{
	if (x != p[x])
		p[x] = Find(p[x]);
	return p[x];
}

void Union(int x, int y)
{
	int px = Find(x), py = Find(y);
	if (px == py) return;
	if (Rank[px] < Rank[py])
	{
		Rank[py]++;
		p[px] = py;
	}
	else
	{
		Rank[px]++;
		p[py] = px;
	}
}

int Kruskal(int x)
{
	int n = 0, Sum = 0;
	for (int i = 0; i < M; i++)
	if (edge[i].can)
	{
		int u = edge[i].u, v = edge[i].v;
		if (Find(u) != Find(v))
		{
			if (x == -1) edge[i].use = 1;
			Sum += edge[i].w;
			Union(u, v);
			n++;
		}
		if (n == N - 1) return Sum;
	}
	return inf;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d", &N, &M);
		for (int i = 0; i < M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			edge[i].u = u;
			edge[i].v = v;
			edge[i].w = w;
			edge[i].use = 0;
			edge[i].can = 1;
			addEdge(u, v, w);
			addEdge(v, u, w);
		}
		if (N == 1)
		{
			printf("0 -1\n");
			continue;
		}

		sort(edge, edge + M, cmp);
		for (int i = 1; i <= N; i++)
		{
			p[i] = i;
			Rank[i] = 0;
		}
		int res1 = Kruskal(-1);
		printf("%d ", res1);
		int Min = inf;
		for (int i = 0; i < M; i++)
		{
			if (edge[i].use)
			{
				for (int j = 1; j <= N; j++)
				{
					p[j] = j;
					Rank[j] = 0;
				}
				edge[i].can = 0;
				int temp = Kruskal(0);
				if (temp < Min) Min = temp;
				edge[i].can = 1;
			}
		}
		if (Min == inf) Min = -1;
		printf("%d\n", Min);
	}
	return 0;
}

