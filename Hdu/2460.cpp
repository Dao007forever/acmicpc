#pragma comment(linker, "/STACK:1024000000,1024000000")
/*
 * Author: Yang Zhang
 * Created Time: Sun 26 Aug 2012 02:18:31 PM CST
 * File Name: 2460.cpp
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 100005
#define MAXM 400005
int n, m, q, numBri;
vector<pair<int, int> > adj[MAXN];
int dfn[MAXN], low[MAXN], isBridge[MAXN], fa[MAXN];
bool visit[MAXM];

void addEdge(int u, int v, int id) {
	adj[u].PB(MP(v, id));
}

void Tarjan(int u, int dep) {
	dfn[u] = low[u] = dep;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i].first, id = adj[u][i].second;
		if (dfn[v] == -1) {
			fa[v] = u;
			visit[id] = true;
			Tarjan(v, dep + 1);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				isBridge[v] = 1;
				numBri++;
			}
		} else if (!visit[id]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

void Bridge() {
	memset(isBridge, 0, sizeof(isBridge));
	for (int i = 0; i < n; i++) dfn[i] = -1;
	fa[0] = 0;
	Tarjan(0, 0);
}

void lca(int x, int y) {
	if (dfn[x] < dfn[y]) swap(x, y);
	//x and y are in the same chain
	while (dfn[x] > dfn[y]) {
		if (isBridge[x]) {
			numBri--;
			isBridge[x] = 0;
		}
		x = fa[x];
	}
	//x and y are in the different chain
	while (x != y) {
		if (isBridge[x]) {
			numBri--;
			isBridge[x] = 0;
		}
		if (isBridge[y]) {
			numBri--;
			isBridge[y] = 0;
		}
		x = fa[x]; y = fa[y];
	} 
}

int main() {
	for (int cas = 1; scanf("%d%d", &n, &m) && n; cas++) {
		for (int i = 0; i <= n; i++) adj[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			addEdge(a, b, i);
			addEdge(b, a, i);
		}
		numBri = 0;
		Bridge();
		printf("Case %d:\n", cas);
		scanf("%d", &q);
		while (q--) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			lca(a, b);
			printf("%d\n", numBri);
		}
		puts("");
	}
	return 0;
}

