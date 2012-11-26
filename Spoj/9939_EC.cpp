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
 
const int MAXN = 20000 + 10;
const int MAXM = 200000 + 10;
struct Edge
{
    int v, next;
}edge[4 * MAXM];
int N, M, Top, Size, Index, num;
int Stack[MAXN], Head[MAXN], id[MAXN], low[MAXN], dfn[MAXN], vis[MAXN];
int a[MAXN], b[MAXN];

void addEdge(int u, int v)
{
//	cout << u << " " << v << endl;
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
        }
    }
}
 
void init()
{
    num = Top = Size = Index = 0;
    memset(Head, -1, sizeof(Head));
    memset(Stack, 0, sizeof(Stack));
    memset(id, 0, sizeof(id));
    memset(vis, 0, sizeof(vis));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
 
    scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
		if (a[i] == 3) b[i] = 1;
		else b[i] = a[i] + 1;
	}
	for (int i = 1; i <= M; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		if (z == 1)
		{
			if (a[x] == a[y])
			{
				addEdge(x, y + N);
				addEdge(y, x + N);
//				addEdge(x + N, y);
			}
			if (a[x] == b[y])
			{
				addEdge(x, y);
				addEdge(y + N, x + N);
//				addEdge(x + N, y + N);
			}
			if (b[x] == a[y])
			{
				addEdge(x + N, y + N);
				addEdge(y, x);
//				addEdge(x, y);
			}
			if (b[x] == b[y])
			{
				addEdge(x + N, y);
				addEdge(y + N, x);
//				addEdge(x, y + N);
			}
		}
		else
		{
			if (a[x] != a[y])
			{
				addEdge(x, y + N);
				addEdge(y, x + N);
//				addEdge(x + N, y);
			}
			if (a[x] != b[y])
			{
				addEdge(x, y);
				addEdge(y + N, x + N);
//				addEdge(x + N, y + N);
			}
			if (b[x] != a[y])
			{
				addEdge(x + N, y + N);
				addEdge(y, x);
//				addEdge(x, y);
			}
			if (b[x] != b[y])
			{
				addEdge(x + N, y);
				addEdge(y + N, x);
//				addEdge(x, y + N);
			}
		}
	}
}

void solve()
{
	for (int i = 1; i <= 2 * N; i++)
		if (!dfn[i]) Tarjan(i);
	bool flag = true;
	for (int i = 1; i <= N; i++)
		if (id[i] == id[i + N])
		{
			flag = false;
			break;
		}
	if (flag) puts("yes");
	else puts("no");
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	int cas = 1;
	while (Test--)
	{
		printf("Case #%d: ", cas++);
		init();
		solve();
	}
	return 0;

}
