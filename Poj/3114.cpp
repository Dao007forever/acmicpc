/*
 * Author: Yang Zhang
 * Created Time: Sun 26 Aug 2012 12:47:11 PM CST
 * File Name: 3114.cpp
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

#define MAXN 505
const int inf = 1<<29;
struct Graph {
	int n, size, depth;
	vector<pair<int, int> > adj[MAXN];
	int low[MAXN], dfn[MAXN], id[MAXN];
	bool vis[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
	}

	void addEdge(int u, int v, int w) {
		adj[u].PB(MP(v, w));
	}

	void Tarjan(int u) {
		dfn[u] = low[u] = depth++;
		S.push(u);
		vis[u] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
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

	int dis[MAXN][MAXN];
	priority_queue<pair<int, int> > q;
	void dijkstra(int st) {
		for (int i = 0; i <= n; i++) {
			dis[st][i] = inf, vis[i] = false;
		}
		dis[st][st] = 0;
		q.push(MP(0, st));
		while (!q.empty()) {
			int u = q.top().second; q.pop();
			vis[u] = true;
			for (int i = 0; i < adj[u].size(); i++) {
				int v = adj[u][i].first, w = adj[u][i].second;
				if (!vis[v] && dis[st][u] + w < dis[st][v]) {
					dis[st][v] = dis[st][u] + w;
					q.push(MP(-dis[st][v], v));
				}
			}
		}
	}

}g, newg;

int main() {
	int n, m, q;
	int blank = false;
	while (scanf("%d%d", &n, &m) && n) {
		if (blank) puts("");
		blank = true;
		g.init(n);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			g.addEdge(a, b, c);
		}
		g.SCC();
		newg.init(g.size);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < g.adj[i].size(); j++) {
				int u = g.id[i], v = g.id[g.adj[i][j].first], w = g.adj[i][j].second;
				if (u == v) continue;
				newg.addEdge(u, v, w);
			}
		for (int i = 1; i <= newg.n; i++)
			newg.dijkstra(i);
		scanf("%d", &q);
		while (q--) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			a = g.id[a]; b = g.id[b];
			if (a == b) printf("0\n");
			else {
				if (newg.dis[a][b] == inf) printf("Nao e possivel entregar a carta\n");
				else {
					printf("%d\n", newg.dis[a][b]);
				}
			}
		}
	}
	return 0;
}

