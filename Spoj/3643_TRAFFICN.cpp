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

const int MAXN = 10000 + 10;
const int MAXM = 100000 + 10;
const int inf = 1000000000;
struct Edge
{
	int v, w, next;
}edge[MAXM], revedge[MAXM];
int N, M, K, S, T;
int vis[MAXN], dis[2][MAXN];
int num, Head[MAXN];
int revnum, revHead[MAXN];

void init()
{
	num = revnum = 0;
	memset(Head, -1, sizeof(Head));
	memset(revHead, -1, sizeof(revHead));
}

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;

	revedge[revnum].v = u;
	revedge[revnum].w = w;
	revedge[revnum].next = revHead[v];
	revHead[v] = revnum++;
}

void Spfa(int idx, int sta)
{
	for (int i = 1; i <= N; i++)
	{
		vis[i] = false;
		dis[idx][i] = inf;
	}
	vis[sta] = true;
	dis[idx][sta] = 0;
	queue<int> Q;
	Q.push(sta);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		if (!idx)
		{
			for (int i = Head[u]; i != -1; i = edge[i].next)
			{
				int v = edge[i].v;
				if (dis[idx][u] + edge[i].w < dis[idx][v])
				{
					dis[idx][v] = dis[idx][u] + edge[i].w;
					if (!vis[v])
					{
						vis[v] = true;
						Q.push(v);
					}
				}
			}
		}
		else 
		{
			for (int i = revHead[u]; i != -1; i = revedge[i].next)
			{
				int v = revedge[i].v;
				if (dis[idx][u] + revedge[i].w < dis[idx][v])
				{
					dis[idx][v] = dis[idx][u] + revedge[i].w;
					if (!vis[v])
					{
						vis[v] = true;
						Q.push(v);
					}
				}
			}
		}
		vis[u] = true;
	}
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		init();
		scanf("%d%d%d%d%d", &N, &M, &K, &S, &T);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w);
		}
		Spfa(0, S);
		Spfa(1, T);
		int ret = dis[0][T];
		for (int i = 1; i <= K; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if (dis[0][u] + dis[1][v] + w < ret)
				ret = dis[0][u] + dis[1][v] + w;
			if (dis[0][v] + dis[1][u] + w < ret)
				ret = dis[0][v] + dis[1][u] + w;
		}
		if (ret == inf) printf("-1\n");
		else printf("%d\n", ret);
	}
	return 0;
}
