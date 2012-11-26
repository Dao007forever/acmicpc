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

const int MAXN = 200000 + 10;
const int MAXM = 300000 + 10;
struct Edge
{
	int v, next;
}edge[MAXM * 6];
int n, m, Index, Top, size;
int Head[MAXN], num;
int low[MAXN], dfn[MAXN], vis[MAXM * 6], Stack[MAXN], id[MAXN];

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

bool x[6 * MAXM], vst[MAXN];
void dfs(int u)
{
	vst[u] = true;
	for (int i = Head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].v;
		if (!x[i ^ 1]) printf("%d %d\n", u, v), x[i] = true;
		if (vst[v]) continue;
		dfs(v);
	}
}

int main()
{
	freopen("a", "r", stdin);
	num = Top = Index = size = 0;
	memset(Head, -1, sizeof(Head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		addEdge(u, v); addEdge(v, u);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) Tarjan(i);
	bool flag = true;
	int now = id[1];
	for (int i = 2; i <= n; i++)
		if (id[i] != now)
		{
			flag = false;
			break;
		}
	if (!flag)
	{
		printf("0\n");
	}else dfs(1);
	return 0;
}
