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
/*------------#include omitted-----------*/
#define MAXN 5005
struct Graph {
	int n, size, depth;
	vector<int> adj[MAXN];
	int low[MAXN], dfn[MAXN], id[MAXN];
	int cnt[MAXN];
	bool vis[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
		memset(cnt, 0, sizeof(cnt));
		memset(id, 0, sizeof(id));
		memset(vis, 0, sizeof(vis));
		while (!S.empty()) S.pop();
	}

	void addEdge(int u, int v) {
		adj[u].PB(v);
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
				vis[v] = false;
			} while (u != v);
		}
	}

	void SCC() {
		memset(dfn, -1, sizeof(dfn));
		size = 0;
		depth = 1;
		for (int i = 0; i < n; i++)
			if (dfn[i] == -1) Tarjan(i);
	}

	int dp[MAXN], tot;
	bool vst[MAXN];

	void dfs(int u) {
		vst[u] = true;
		tot += cnt[u];
		for (int i = 0, v; i < adj[u].size(); i++)
			if (!vst[v = adj[u][i]]) {
				dfs(v);
			}
	}

	void work() {
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			memset(vst, 0, sizeof(vst));
			tot = 0;
			dfs(i);
			dp[i] = tot;
		}
	}

}g, g2;

int n, m;

void build() {
	g2.init(g.size);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < g.adj[i].size(); j++)
			if (g.id[i] != g.id[g.adj[i][j]]) {
				g2.addEdge(g.id[g.adj[i][j]], g.id[i]);
			}
		g2.cnt[g.id[i]]++;
	}
	g2.work();
	int ret = 0;
	for (int i = 1; i <= g2.n; i++)
		ret = max(ret, g2.dp[i]);
	printf("%d\n", ret - 1);
	vector<int> ans;
	for (int i = 0; i < n; i++)
		if (g2.dp[g.id[i]] == ret) ans.push_back(i);
	for (int i = 0; i < ans.size(); i++)
		printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case %d: ", cas);
		scanf("%d%d", &n, &m);
		g.init(n);
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			g.addEdge(a, b);
		}
		g.SCC();
		build();
	}
}
