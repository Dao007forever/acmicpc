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

const int MAXN = 9000 + 10;
const int MAXM = 52000 + 10;
struct Edge
{
	int v, next;
}edge[MAXM], edge2[MAXM];
int N, M, Index, Top, Size;
int num, Head[MAXN], num2, Head2[MAXN];
int low[MAXN], dfn[MAXN], Stack[MAXN], id[MAXN];
int ans[MAXN], cnt[MAXN];
int vis[MAXN], flag[MAXN];
void Tarjan(int u)
{
	low[u] = dfn[u] = ++Index;
	Stack[++Top] = u;
	vis[u] = 1;
	for (int i = Head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].v;
		if (!dfn[v])
		{
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v])
		{
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u])
	{
		Size++;
		for (; Stack[Top + 1] != u; --Top)
		{
			vis[Stack[Top]] = 0;
			id[Stack[Top]] = Size;
		}
	}
}

void addEdge(int u, int v)
{
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void addEdge2(int u, int v)
{
	edge2[num2].v = v;
	edge2[num2].next = Head2[u]++;
	Head2[u] = num2++;
}

void init()
{
	num = num2 = Size = Top = Index = 0;
	memset(Head, -1, sizeof(Head));
	memset(Head2, -1, sizeof(Head2));
	memset(id, 0, sizeof(id));
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(cnt, 0, sizeof(cnt));
	memset(ans, 0, sizeof(ans));
}

void solve()
{
	int Max = 0;
	for (int i = 1; i <= Size; i++)
	{
		queue<int> Q;
		ans[i] = cnt[i];
		Q.push(i);
		flag[i] = i;
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			for (int j = Head2[u]; j != -1; j = edge2[j].next)
				if (flag[edge2[j].v] != i)
				{
					flag[edge2[j].v] = i;
					ans[i] += cnt[edge2[j].v];
					Q.push(edge2[j].v);
				}
		}
		Max = max(Max, ans[i]);
	}
	for (int i = 1; i <= N; i++)
		if (ans[id[i]] == Max)
			printf("%d ", i);
	printf("\n");
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		init();
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			addEdge(u, v);
		}
		for (int i = 1; i <= N; i++)
		if (!dfn[i]) Tarjan(i);

		for (int i = 1; i <= N; i++)
			cnt[id[i]]++;
		for (int u = 1; u <= N; u++)
			for (int i = Head[u]; i != -1; i = edge[i].next)
				if (id[u] != id[edge[i].v])
				{
					addEdge2(id[edge[i].v], id[u]);
				}
		solve();
	}
}
