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
int N, Index, Size, Top, num, Max;
struct Edge
{
	int v, next;
}edge[5 * MAXN];
int a[MAXN], id[MAXN], low[MAXN], dfn[MAXN], vis[MAXN], Stack[MAXN], Head[MAXN], use[MAXN];

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

void AddEdge(int a, int b)
{
	edge[num].v = b;
	edge[num].next = Head[a];
	Head[a] = num++;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	memset(use, 0, sizeof(use));
	Max = 0;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
		use[a[i]] = 1;
		if (a[i] > Max) Max = a[i];
	}
	memset(Head, -1, sizeof(Head));
	num = Size = Index = Top = 0;
	for (int i = 1; i < N; i++)
	{
		if (a[i] != a[i + 1]) AddEdge(a[i], a[i + 1]);
	}
	for (int i = 1; i <= Max; i++)
	if (use[i])
	{
		if (!dfn[i]) Tarjan(i);
	}

	int idx = -1;
	vector<int> res;
	for (int i = 1; i <= N; i++)
	{
		if (id[a[i]] != idx)
		{
			res.push_back(a[i]);
			idx = id[a[i]];
		}
	}

	int n = res.size();
	for (int i = 0; i < n - 1; i++)
		cout << res[i] << " ";
	cout << res[n - 1] << endl;
	return 0;
}
