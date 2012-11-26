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

const int MAXN = 1000 + 10;
const int MAXM = 4000 + 10;
const int inf = 1000000000;
struct Edge
{
	int u, v, next, w;
	int vis;
}edge[MAXM];
int N, M, ans, cnt, num, frob;
int Head[MAXN], dis[MAXN], vis[MAXN], proc[MAXN], Count[MAXN];

void addEdge(int u, int v, int w)
{
	edge[num].u = u;
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
	edge[num].vis = false;
}

void SPFA(int S, int T, int len)
{
	memset(dis, -1, sizeof(dis));
	dis[S] = 0;
	Count[S] = 1;
	proc[S] = 0;
	queue<int> Q;
	Q.push(S);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		if (proc[u] < Count[u])
		{
			for (int i = Head[u]; i != -1; i = edge[i].next)
			if (i > frob)
			{
				if (dis[u] + edge[i].w < dis[edge[i].v] || dis[edge[i].v] == -1)
				{
					dis[edge[i].v] = dis[u] + edge[i].w;
					Count[edge[i].v] = Count[u] - proc[u];
					proc[edge[i].v] = 0;
					Q.push(edge[i].v);
				}
				else if (dis[u] + edge[i].w == dis[edge[i].v])
				{
					if (Count[edge[i].v] == proc[edge[i].v])
						Q.push(edge[i].v);
					Count[edge[i].v] += Count[u] - proc[u];
				}
			}
			proc[u] = Count[u];
		}
	}
	if (dis[T] != -1)
	{
		if (dis[T] + len < ans)
		{
			ans = dis[T] + len;
			cnt = Count[T];
		}
		else if (dis[T] + len == ans)
		{
			cnt += Count[T];
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		num = 0;
		memset(Head, -1, sizeof(Head));

		scanf("%d%d", &N, &M);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w);
			addEdge(v, u, w);
		}

		ans = inf;
		cnt = 0;
		for (int i = 0; i < num; i += 2)
		{
			frob = i + 1;
			SPFA(edge[i].u, edge[i].v, edge[i].w);
		}
		if (ans == inf) ans = 0, cnt = 0;
		printf("%d %d\n", ans, cnt);
	}
	return 0;
}
