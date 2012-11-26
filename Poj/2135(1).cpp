#include <set>
#include <map>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
#include <bitset>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000 + 10;
const int MAXM = 10000 + 10;
const int INF = 0x3f3f3f3f;
int N, M, E;
int source, sink;
int pre[MAXN];
int dis[MAXN], Head[MAXN];
bool vis[MAXN];
struct Edge
{
	int u, v, flow, cost;
	int next;
}edge[MAXM * 4];

void AddEdge(int u, int v, int flow, int cost)
{
	edge[E].u = u; edge[E].v = v; edge[E].flow = flow;
	edge[E].cost = cost; edge[E].next = Head[u]; Head[u] = E++;
	edge[E].u = v; edge[E].v = u; edge[E].flow = 0;
	edge[E].cost = -cost; edge[E].next = Head[v]; Head[u] = E++;
}

bool SPFA()
{
	memset(vis, 0, sizeof(vis));
	memset(pre, 0, sizeof(pre));
	queue<int> Q;
	Q.push(source);
	for (int i = 0; i <= N; i++)
		dis[i] = INF;
	vis[source] = true;
	dis[source] = 0;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int i = Head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].v;
			if (edge[i].flow > 0 && dis[u] + edge[i].flow < dis[v])
			{
				dis[v] = dis[u] + edge[i].flow;
				pre[v] = i;
				if (!vis[v])
				{
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}
	return dis[sink] != INF;
}

void MinCost()
{
	int minCost = 0;
	while (SPFA())
	{
		minCost += dis[N];
		int j = pre[N];
		while (j != -1)
		{
			edge[j].flow--;
			edge[j ^ 1].flow++;
			j = pre[edge[j].u];
		}
	}
	printf("%d\n", minCost);
}

int main()
{
	freopen("a.txt", "r", stdin);
	int N, M;
	scanf("%d%d", &N, &M);
	source = 0;
	sink = N + 1;
	for (int i = 1; i <= M; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		AddEdge(a, b, 1, c);
		AddEdge(b, a, 1, c);
	}
	AddEdge(source, 1, 2, 0);
	AddEdge(N, sink, 2, 0);
	MinCost();
	return 0;
}
