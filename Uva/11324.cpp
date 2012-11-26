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
	int n, size, depth;
	vector<int> adj[MAXN];
	int low[MAXN], dfn[MAXN], id[MAXN];
	bool vis[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
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

}g;

int n, m;
int cnt[MAXN], dp[MAXN];
vector<int> graph[MAXN];

void dfs(int u) {
	if (dp[u] != -1) return;
	dp[u] = 0;
	for (int i = 0; i < graph[u].size(); i++) {
		int v = graph[u][i];
		dfs(v);
		dp[u] = max(dp[u], dp[v]);
	}
	dp[u] += cnt[u];
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		g.init(n);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			g.addEdge(a, b);
		}
		g.SCC();
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++)
			cnt[g.id[i]]++;
		for (int u = 0; u < n; u++) {
			for (int i = 0; i < g.adj[u].size(); i++) {
				int v = g.adj[u][i];
				int a = g.id[u], b = g.id[v];
				if (a != b) {
					graph[b].PB(a);
				}
			}
		}
		memset(dp, -1, sizeof(dp));
		for (int i = 1; i <= g.size; i++)
			dfs(i);
		int ret = 0;
		for (int i = 1; i <= g.size; i++)
			ret = max(ret, dp[i]);
		printf("%d\n", ret);
		for (int i = 0; i <= g.size; i++) graph[i].clear();
	}
	return 0;
}