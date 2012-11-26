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
const int MAXM = 500000 + 10;
struct Mystring
{
	char s[20];
	friend bool operator<(const Mystring& a, const Mystring& b)
	{
		return strcmp(a.s, b.s) < 0;
	}
};
map<Mystring, int> si;
int N, M, pid;
struct E
{
	Mystring x, y;
	bool isBridge;
}pe[MAXM];
struct Edge
{
	int u, v, next;
}edge[MAXM];
int Head[MAXN], num;
int dfn[MAXN], low[MAXN], Index, vis[MAXN];

void init()
{
	si.clear();
	pid = 0;
	memset(Head, -1, sizeof(Head));
	memset(dfn, 0, sizeof(dfn));
	num = Index = 0;
}

void addEdge(int u, int v)
{
	edge[num].u = u;
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void Tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++Index;
	for (int i = Head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].v;
		if (v == fa)
			continue;
		if (!dfn[v])
			Tarjan(v, u);
		low[u] = min(low[u], low[v]);
	}
}

void findBridge()
{
	int u, v, ans = 0;
	for (int i = 0; i < M; i++)
	{
		u = si[pe[i].x], v = si[pe[i].y];
		if (low[v] > dfn[u] || low[u] > dfn[v])
		{
			pe[i].isBridge = true;
			ans++;
		}
	}
	printf("%d\n", ans);
	for (int i = 0; i < M; i++)
		if (pe[i].isBridge)
			printf("%s %s\n", pe[i].x.s, pe[i].y.s);
}

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &M);
		init();
		for (int i = 0; i < M; i++)
		{
			int u, v;
			scanf("%s %s", pe[i].x.s, pe[i].y.s);
			pe[i].isBridge = false;

			if (si.find(pe[i].x) == si.end())
				si[pe[i].x] = ++pid;
			if (si.find(pe[i].y) == si.end())
				si[pe[i].y] = ++pid;

			u = si[pe[i].x], v = si[pe[i].y];
			addEdge(u, v);
			addEdge(v, u);
		}
		Tarjan(1, -1);
		bool notConnected = false;
		for (int i = 1; i <= N; i++)
		{
			if (!dfn[i])
			{
				notConnected = true;
				break;
			}
		}

		if (notConnected)
			puts("0");
		else findBridge();
	}
	return 0;
}
