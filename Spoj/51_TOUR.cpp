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
struct Edge
{
	int v, next;
}edge[MAXN * 1000];
int N, num, Size, Top, Index;
int Head[MAXN], Stack[MAXN], vis[MAXN], id[MAXN], dfn[MAXN], low[MAXN];
int deg[MAXN], Count[MAXN];

void addEdge(int u, int v)
{
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}
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
			Count[Size]++;
		}
	}
}
void solve()
{
	for (int i = 1; i <= N; i++)
	if (!dfn[i]) Tarjan(i);
}
int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		num = Top = Size = Index = 0;
		memset(Head, -1, sizeof(Head));
		memset(Stack, 0, sizeof(Stack));
		memset(id, 0, sizeof(0));
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(vis, 0, sizeof(vis));
		memset(deg, 0, sizeof(deg));
		memset(Count, 0, sizeof(Count));

		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			int x, k;
			scanf("%d", &x);
			for (int j = 1; j <= x; j++)
			{
				scanf("%d", &k);
				addEdge(i, k);
			}
		}

		solve();
		for (int u = 1; u <= N; u++)
			for (int i = Head[u]; i != -1; i = edge[i].next)
			{
				if (id[u] != id[edge[i].v])
				{
					deg[id[edge[i].v]] = 1;
				}
			}

		int cnt = 0, k = 0;
		for (int i = 1; i <= Size; i++)
		if (!deg[i])
		{
			cnt++;
			k += Count[i];
		}
		if (cnt == 1)
		{
			/*int ans = 0;
			for (int i = 1; i <= N; i++)
			if (id[i] == k) ans++;
			printf("%d\n", ans);*/
			printf("%d\n", k);
		}
		else printf("0\n");
	}
	return 0;
}
