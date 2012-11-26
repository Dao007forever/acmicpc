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

#define MAXN 50005
const int inf = 100000000;
int n, m;
int cnt[MAXN], represent[MAXN];
struct Graph {
	int n, size, depth;
	int dfn[MAXN], low[MAXN], id[MAXN], ind[MAXN];
	bool vis[MAXN];
	vector<int> adj[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
		memset(id, 0, sizeof(id));
		memset(dfn, -1, sizeof(dfn));
		memset(ind, 0, sizeof(ind));
		depth = 1; size = 0;
		while (!S.empty()) S.pop();
	}

	void addEdge(int u, int v) {
		adj[u].PB(v);
		ind[v]++;
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
				if (v < represent[size])
					represent[size] = v;
				cnt[size]++;
				id[v] = size;
				vis[v] = false;
			} while (u != v);
		}
	}

	void SCC() {
		for (int i = 1; i <= n; i++)
			if (dfn[i] == -1) Tarjan(i);
	}

	int dp[MAXN], p[MAXN];
	void dfs(int u) {
		if (dp[u] > 0) return;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			dfs(v);
			if (dp[v] > dp[u] || dp[v] == dp[u] && represent[p[v]] < represent[p[u]]) {
				dp[u] = dp[v];
				p[u] = p[v];
			}
		}
		if (dp[u] == 0) p[u] = u;
		dp[u] += cnt[u];
	}

	void solve() {
		memset(dp, 0, sizeof(dp));
		memset(p, -1, sizeof(p));
		for (int i = 1; i <= n; i++)
			if (dp[i] == 0) dfs(i);
		int ret = 0;
		pair<int, int> ans = MP(MAXN, MAXN);
		for (int i = 1; i <= n; i++) {
			int a = represent[i], b = represent[p[i]];
			pair<int, int> tmp = MP(b, a);
			if (dp[i] > ret) {
				ret = dp[i];
				ans = tmp;
			} else if (dp[i] == ret && (tmp < ans && ans.first != ans.second || tmp.first == tmp.second)) {
				ans = tmp;
			}
		}
		printf("%d\n", ret);
		if (ans.first == ans.second) ans = MP(1, 2);
		printf("%d %d\n", ans.first, ans.second);
	}
}g, newg;

void build() {
	for (int u = 1; u <= n; u++)
		for (int i = 0; i < g.adj[u].size(); i++) {
			int v = g.adj[u][i];
			if (g.id[u] != g.id[v]) {
				newg.addEdge(g.id[u], g.id[v]);
			}
		}
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		memset(cnt, 0, sizeof(cnt));
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			represent[i] = inf;
		g.init(n);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			g.addEdge(a, b);
		}
		g.SCC();

		int size = g.size;
		newg.init(size);
		build();
		newg.solve();
	}
	return 0;
}

