#include <map>
#include <set>
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

const int MAXN = 3000 + 10;
const int MAXM = 10000 + 10;
const int inf = 10000000;
struct Edge
{
        int v, next, cost;
}edge[MAXM * 5], e[MAXN * 5];
int N, M;
int Head[MAXN], list[MAXN];
int low[MAXN], dfn[MAXN], Index, Top, size;
int vis[MAXM], deg[MAXN], Stack[MAXN], id[MAXN];
int dis[MAXN], Ind, num, x[MAXN], y[MAXN], cnt[MAXN];

void AddEdge(int u, int v, int num)
{
        edge[num].v = v; edge[num].next = Head[u]; Head[u] = num;
}

void addEdge(int u, int v) {
	e[num].v = v;
	e[num].cost = 1;
	e[num].next = list[u];
	list[u] = num++;
}

void Tarjan(int u)
{
        low[u] = dfn[u] = ++Index;
        Stack[++Top] = u;
        for (int i = Head[u]; i != -1; i = edge[i].next)
        if (!vis[i])
        {
                vis[i] = vis[i ^ 1] = 1;
                if (!dfn[edge[i].v])
                {
                        Tarjan(edge[i].v);
                        low[u] = min(low[u], low[edge[i].v]);
                }
                else low[u] = min(low[u], dfn[edge[i].v]);
        }
        if (low[u] == dfn[u])
        {
                size++;
                for (;Stack[Top + 1] != u; --Top)
                        id[Stack[Top]] = size;
        }
}
void spfa(int st)
{
	for (int i = 1; i <= size; i++)
		dis[i] = inf;
	dis[st] = 0;
	memset(vis, 0, sizeof(vis));
	vis[st] = 1;
	queue<int> Q;
	Q.push(st);
	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for (int i = list[v]; i != -1; i = e[i].next)
		{
			if (dis[v] + e[i].cost < dis[e[i].v])
			{
				dis[e[i].v] = dis[v] + e[i].cost;
				if (!vis[e[i].v])
				{
					vis[e[i].v] = true;
					Q.push(e[i].v);
				}
			}
		}
		vis[v] = false;
	}
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d", &N);
	num = 0;
	memset(list, -1, sizeof(list));
	memset(Head, -1, sizeof(Head));
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &x[i], &y[i]);
		int m1 = 2 * i, m2 = m1 ^ 1;
		AddEdge(x[i], y[i], m1);
		AddEdge(y[i], x[i], m2);
	}
	for (int i = 1; i <= N; i++)
		if (!dfn[i]) Tarjan(i);

	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < N; i++) {
		addEdge(id[x[i]], id[y[i]]);
		addEdge(id[y[i]], id[x[i]]);
	}
	for (int i = 1; i <= N; i++) {
		cnt[id[i]]++;
		if (cnt[id[i]] > 1) {
			Ind = id[i];
		}
	}
	for (int i = 1; i <= size; i++)
		if (i == Ind) {
			spfa(i);
			break;
		}
	for (int i = 1; i < N; i++)
		printf("%d ", dis[id[i]]);
	printf("%d\n", dis[id[N]]);
	return 0;
}
