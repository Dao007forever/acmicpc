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

const int MAXN = 1200;;
const int MAXM = 1200000;
const int inf = 0x3f3f3f3f;
#define abs(x) ((x) > 0 ? (x) : -(x))
struct Point
{
	int x, y, z;
}p[MAXN];
struct Edge
{
	int u, v, w;
}edge[MAXM];
int pre[MAXN], id[MAXN], vis[MAXN], in[MAXN];
int N, M;

void addEdge(int u, int v, int w)
{
	edge[M].u = u;
	edge[M].v = v;
	edge[M++].w = w;
}

int dist(Point a, Point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}

int directedMST(int root)
{
	int res = 0, nv = N;
	while (1)
	{
		for (int i = 0; i < nv; i++)
		{
			in[i] = inf;
		}
		for (int i = 0; i < M; i++)
		{
			int u = edge[i].u, v = edge[i].v;
			if (edge[i].w < in[v] && u != v)
			{
				pre[v] = u;
				in[v] = edge[i].w;
			}
		}
		for (int i = 0; i < nv; i++)
		{
			if (i == root) continue;
			if (in[i] == inf) return -1;
		}
		int cntnode = 0;
		memset(id, -1, sizeof(id[0]) * (nv + 3));
		memset(vis, -1, sizeof(vis[0]) * (nv + 3));
		in[root] = 0;
		for (int i = 0; i < nv; i++)
		{
			res += in[i];
			int v = i;
			while (vis[v] != i && id[v] == -1 && v != root)
			{
				vis[v] = i;
				v = pre[v];
			}
			if (v != root && id[v] == -1)
			{
				for (int u = pre[v]; u != v; u = pre[u])
				{
					id[u] = cntnode;
				}
				id[v] = cntnode++;
			}
		}
		if (cntnode == 0) break;
		for (int i = 0; i < nv; i++)
		{
			if (id[i] == -1) id[i] = cntnode++;
		}
		for (int i = 0; i < M; i++)
		{
			int v = edge[i].v;
			edge[i].u = id[edge[i].u];
			edge[i].v = id[edge[i].v];
			if (edge[i].u != edge[i].v)
			{
				edge[i].w -= in[v];
			}
		}
		nv = cntnode;
		root = id[root];
	}
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	int x, y, z;
	while (scanf("%d%d%d%d", &N, &x, &y, &z) != EOF)
	{
		if (N == 0 && x == 0 && y == 0 && z == 0) break;
		M = 0;
		N++;
		for (int i = 1; i < N; i++)
		{
			scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].z);
			addEdge(0, i, x * p[i].z);
		}
		for (int i = 1; i < N; i++)
		{
			int k, t;
			scanf("%d", &k);
			while (k--)
			{
				scanf("%d", &t);
				if (t == i) continue;
				int cost = dist(p[i], p[t]) * y;
				if (p[t].z > p[i].z) cost += z;
				addEdge(i, t, cost);
			}
		}
		printf("%d\n", directedMST(0));
	}
	return 0;
}
