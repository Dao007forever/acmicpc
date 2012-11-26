/*
 * Author : Yang Zhang
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

#define MAXN 10005
#define MAXM 100005
int n, m, q;
int dfn[MAXN], low[MAXN], p[MAXN], vis[MAXM];
vector<pair<int, int> > adj[MAXN];

int find(int x) {
	return p[x] == x ? x : (p[x] = find(p[x]));
}

void Tarjan(int u, int dep) {
	low[u] = dfn[u] = dep;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i].first, id = adj[u][i].second;
		if (dfn[v] == -1) {
			vis[id] = true;
			Tarjan(v, dep + 1);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				p[find(u)] = find(v);
			}
		} else if (!vis[id]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		if (n + m + q == 0) break;
		for (int i = 1; i <= n; i++) {
			p[i] = i;
			dfn[i] = -1;
			low[i] = 0;
			adj[i].clear();
		}
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			adj[a].PB(MP(b, i)); adj[b].PB(MP(a, i));
		}
		for (int i = 1; i <= n; i++)
			if (dfn[i] == -1) {
				Tarjan(i, 0);
			}
		while (q--) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (find(a) == find(b)) puts("Y");
			else puts("N");
		}
		puts("-");
	}
	return 0;
}
