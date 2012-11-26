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

#define MAXN 1005
struct Graph {
	int n;
	vector<int> adj[MAXN];
	int cnt[MAXN], dfn[MAXN], low[MAXN], id[MAXN], p[MAXN];
	bool vst[MAXN], vis[MAXN];
	int size, depth;
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
	}

	void Tarjan(int u) {
		dfn[u] = low[u] = depth++;
		S.push(u);
		vis[u] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dfn[v] == -1) {
				Tarjan(v);
				low[u] = min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			size++;
			int v;
			do {
				v = S.top();
				S.pop();
				id[v] = size;
				cnt[size]++;
				vis[v] = false;
			} while (u != v);
		}
	}

	void SCC() {
		memset(cnt, 0, sizeof(cnt));
		memset(vis, 0, sizeof(vis));
		memset(dfn, -1, sizeof(dfn));
		memset(id, 0, sizeof(id));
		while (!S.empty()) S.pop();
		size = 0; depth = 1;
		for (int i = 0; i < n; i++)
			if (dfn[i] == -1) Tarjan(i);
	}

	void addEdge(int a, int b) {
		adj[a].PB(b);
	}

	void dfs(int u, int source) {
		vst[u] = true;
		for (int i = 0, v; i < adj[u].size(); i++)
			if (!vst[v = adj[u][i]]) {
				p[v] += cnt[source];
				dfs(v, source);
			}
	}

	void solve() {
		memset(p, 0, sizeof(p));
		for (int i = 1; i <= n; i++) {
			memset(vst, 0, sizeof(vst));
			dfs(i, i);
		}
	}

	void output() {
		int ret = 0;
		for (int i = 1; i <= n; i++)
			ret += cnt[i] * (p[i] + cnt[i]);
		printf("%d\n", ret);
	}
}g, g2;
int n, m;
vector<pair<int, int> > edge;

void build() {
	g2.init(g.size);
	for (int i = 0; i < edge.size(); i++) {
		int x = g.id[edge[i].first], y = g.id[edge[i].second];
		if (x != y) g2.addEdge(y, x);
	}
	for (int i = 1; i <= g2.n; i++)
		g2.cnt[i] = g.cnt[i];
}

int main() {
	freopen("in", "r", stdin);
	while (~scanf("%d%d", &n, &m)) {
		edge.clear();
		g.init(n);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			edge.PB(MP(a, b));
			g.addEdge(a, b);
		}
		g.SCC();
		build();
		g2.solve();
		g2.output();
	}
	return 0;
}
