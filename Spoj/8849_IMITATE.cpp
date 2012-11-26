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
#define fi first
#define se second
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

int n, m, sccnt, ret;
int cnt[MAXN];
bool vis[MAXN];
vector<int> adj[MAXN];

void build() {
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i <= sccnt; i++) adj[i].clear();
	for (int u = 0; u < n; u++) {
		cnt[g.id[u]]++;
		for (int i = 0, v; i < g.adj[u].size(); i++) {
			if (g.id[u] != g.id[v = g.adj[u][i]]) {
				adj[g.id[u]].PB(g.id[v]);
			}
		}
	}
}

int getMin() {
	ret = 0;
	for (int i = 1; i <= sccnt; i++) {
		ret += cnt[i] > 1 ? cnt[i] : 0;
	}
	for (int s = 1; s <= sccnt; s++) {
		std::vector<int> d(sccnt + 1, 0);
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < adj[u].size(); i++) {
				int v = adj[u][i];
				if (d[u] + 1 > d[v]) {
					d[v] = d[u] + 1;
					q.push(v);
				}
			}
		}
		for (int i = 1; i <= sccnt; i++)
			ret += d[i] == 1;
	}
	return ret;
}

void dfs(int u, int st) {
	vis[u] = true;
	if (u != st) ret += cnt[u] * cnt[st];
	for (int i = 0, v; i < adj[u].size(); i++)
		if (!vis[v = adj[u][i]])
			dfs(v, st);
}

int getMax() {
	ret = 0;
	for (int i = 1; i <= sccnt; i++) {
		memset(vis, 0, sizeof(vis));
		dfs(i, i);
		ret += cnt[i] * (cnt[i] - 1);
	}
	return ret;
}

void work() {
	scanf("%d%d", &n, &m);
	g.init(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		g.addEdge(a - 1, b - 1);
	}
	g.SCC();
	sccnt = g.size;
	build();
	printf("%d %d\n", getMin(), getMax());
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case #%d: ", cas);
		work();
	}
	return 0;
}
