/*
 * Author: Yang Zhang
 * Created Time: Tue 18 Sep 2012 10:14:27 AM CST
 * File Name: 2682.cpp
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
const int inf = 0x3f3f3f3f;
struct Graph {
	int n, size, depth;
	vector<int> adj[MAXN];
	int low[MAXN], dfn[MAXN], id[MAXN];
	bool vis[MAXN];
	int cnt[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
		memset(cnt, 0, sizeof(cnt));
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
		memset(id, 0, sizeof(id));
		memset(vis, 0, sizeof(vis));
		while (!S.empty()) S.pop();
		memset(dfn, -1, sizeof(dfn));
		size = 0;
		depth = 1;
		for (int i = 0; i < n; i++)
			if (dfn[i] == -1) Tarjan(i);
	}

	int dp[MAXN];
	int dfs(int u) {
		if (dp[u] != -1) return dp[u];
		dp[u] = 0;
		if (adj[u].size() == 0) {
			if (cnt[u] >= 2) {
				return dp[u] = cnt[u];
			} else {
				return 0;
			}
		}
		for (vector<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
			int v = *it;
			int sum = dfs(v);
			if (sum == 0) return 0;
			dp[u] += sum;
		}
		return dp[u] += cnt[u];

	}

	void solve() {
		memset(dp, -1, sizeof(dp));
		int ret = 0;
		for (int i = 1; i <= n; i++) {
			if (cnt[i] >= 2) {
				dfs(i);
				ret = max(ret, dp[i]);
			}
		}
		printf("%d\n", ret);
	}

}g, newg;

int n, m;
int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		g.init(n);
		for (int i = 0; i < m; i++) {
			int id, k, x;
			scanf("%d%d", &id, &k); id--;
			while (k--) {
				scanf("%d", &x); x--;
				g.addEdge(id, x);
			}
		}
		g.SCC();

		newg.init(g.size);
		for (int i = 0; i < n; i++) {
			for (vector<int>::iterator it = g.adj[i].begin(); it != g.adj[i].end(); it++) {
				int j = *it;
				if (g.id[i] != g.id[j]) {
					newg.addEdge(g.id[i], g.id[j]);
				}
			}
			newg.cnt[g.id[i]]++;
		}
		newg.solve();
	}
	return 0;
}

