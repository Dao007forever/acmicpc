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
const int MAXM = 6000 + 10;
struct Edge
{
	int v, next;
}edge[2 * MAXM];
int T, N, M, Index, Size, Top;
int mat[MAXN][MAXN];
int vis[MAXN];
int Head[MAXN], Stack[MAXN], id[MAXN];
int deg[MAXN];
int low[MAXN], dfn[MAXN];
queue<int> Q;

void AddEdge(int u, int v, int num)
{
	edge[num].v = v; edge[num].next = Head[u]; Head[u] = num;
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
		}
	}
}

int TopoSort()
{
	while (!Q.empty())
		Q.pop();
	for (int i = 1; i <= Size; i++)
	{
		deg[i] = 0;
		for (int j = 1; j <= Size; j++)
			deg[i] += mat[j][i];
	}
	for (int i = 1; i <= Size; i++)
	if (deg[i] == 0)
	{
		if (!Q.empty()) return false;
		Q.push(i);
	}
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int i = 1; i <= Size; i++)
		if (mat[u][i])
		{
			mat[u][i] = 0;
			deg[i]--;
			if (deg[i] == 0)
			{
				if (!Q.empty()) return false;
				Q.push(i);
			}
		}
	}
	return true;
}

int main()
{
	freopen("a.txt", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		memset(Stack, 0, sizeof(Stack));
		memset(vis, 0, sizeof(vis));
		memset(low, 0, sizeof(low));
		memset(dfn, 0, sizeof(dfn));
		memset(Head, -1, sizeof(Head));
		memset(id, 0, sizeof(id));
		memset(deg, 0, sizeof(deg));
		scanf("%d%d", &N, &M);
		for (int i = 0; i <= M; i++)
		{
			edge[i].v = 0;
			edge[i].next = 0;
		}
		for (int i = 0; i < M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			AddEdge(u, v, i);
		}
		Index = 0;
		Size = 0;
		Top = 0;
		for (int i = 1; i <= N; i++)
		if (!dfn[i])
			Tarjan(i);

		for (int i = 1; i <= Size; i++)
		for (int j = 1; j <= Size; j++)
			mat[i][j] = 0;
		for (int i = 1; i <= N; i++)
		{
			for (int j = Head[i]; j != -1; j = edge[j].next)
			{
				int v = edge[j].v;
				if (id[i] != id[v])
					mat[id[i]][id[v]] = 1;
			}
		}

		if (TopoSort()) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
