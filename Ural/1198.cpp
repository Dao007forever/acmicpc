/*
 *  强联通分量，然后统计入度为0的那个连通分量，如果只有一个这样的连通分量，那个这个连通分量中的点都可以到达其他所有点
 */
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

const int maxn = 2005;
const int maxm = 2000 * maxn;
struct Edge {
	int v, next;
}edge[maxm];
int num, Head[maxn];
int low[maxn], dfn[maxn], Stack[maxn], id[maxn], vis[maxn], indeg[maxn];
int Index, Size, Top;
int N;

void Tarjan(int u) 
{
	low[u] = dfn[u] = ++Index;
	Stack[++Top] = u;
	vis[u] = 1;
	for (int i = Head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		Size++;
		for (; Stack[Top + 1] != u; --Top) {
			vis[Stack[Top]] = 0;
			id[Stack[Top]] = Size;
		}
	}
}

void addEdge(int u, int v) {
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int main()
{
	freopen("in", "r", stdin);
	num = Top = Size = Index = 0;
	memset(Head, -1, sizeof(Head));
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int x;
		for (; scanf("%d", &x) && x; ) {
			addEdge(i, x);
		}
	}

	for (int i = 1; i <= N; i++)
		if (!dfn[i]) Tarjan(i);
	for (int i = 1; i <= N; i++) {
		for (int j = Head[i]; j != -1; j = edge[j].next) {
			if (id[edge[j].v] != id[i])
				indeg[id[edge[j].v]]++;
		}
	}
	int cnt = 0, ret;
	for (int i = 1; i <= Size; i++)
		if (!indeg[i])
			cnt++, ret = i;
	if (cnt == 1) {
		for (int i = 1; i <= N; i++)
			if (id[i] == ret)
				printf("%d ", i);
	}
	printf("0\n");
	return 0;
}
