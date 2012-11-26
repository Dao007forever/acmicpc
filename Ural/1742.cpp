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

const int MAXN = 100000 + 10;
struct Edge
{
	int v, next;
}edge[5 * MAXN];
int N, num, Size, Top, Index;
int low[MAXN], dfn[MAXN], Stack[10 * MAXN], Head[MAXN], id[MAXN], vis[MAXN];
vector<int> gra[MAXN];

void AddEdge(int a, int b)
{
	edge[num].v = b;
	edge[num].next = Head[a];
	Head[a] = num++;
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
		for (; Stack[Top + 1] != u; Top--)
		{
			vis[Stack[Top]] = 0;
			id[Stack[Top]] = Size;
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	memset(Head, -1, sizeof(Head));
	scanf("%d", &N);
	num = 0;
	for (int i = 1; i <= N; i++)
	{
		int u;
		scanf("%d", &u);
		if (i != u)
		{
			AddEdge(i, u);
			gra[i].push_back(u);
		}
	}

	Index = Size = Top = 0;
	for (int i = 1; i <= N; i++)
	if (!dfn[i])
	{
		Tarjan(i);
	}

	set<int> S;
	for (int i = 1; i <= N; i++)
		if (gra[i].size() > 0 && id[i] != id[gra[i][0]])
		{
			S.insert(id[gra[i][0]]);
		}
	cout << Size - S.size() << " " << Size << endl;
}
