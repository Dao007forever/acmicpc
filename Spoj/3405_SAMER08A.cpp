/*
 * Author: Yang Zhang
 * Created Time: Sat 15 Sep 2012 06:45:34 PM CST
 * File Name: 3405_SAMER08A.cpp
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
const int inf = 0x3f3f3f3f;
struct edge {
	int v, w;
	bool mk;
	edge() {}
	edge(int v, int w, bool mk) : v(v), w(w), mk(mk) {}
};
struct Graph {
	int n;
	int d[MAXN];
	bool vis[MAXN];
	vector<edge> adj[MAXN];

	Graph() {}
	Graph(int n) {
		this->n = n;
		for (int i = 0; i < n; i++) adj[i].clear();
	}

	void addEdge(int u, int v, int w) {
		adj[u].PB(edge(v, w, true));
	}

	priority_queue<pair<int, int> > q;
	void dijkstra(int st) {
		memset(d, 63, sizeof(d));
		memset(vis, 0, sizeof(vis));
		q.push(MP(0, st)); d[st] = 0;
		while (!q.empty()) {
			int u = q.top().second; q.pop();
			vis[u] = true;
			for (vector<edge>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
				int v = it->v, w = it->w;
				if (it->mk && !vis[v] && d[u] + w < d[v]) {
					d[v] = d[u] + w;
					q.push(MP(-d[v], v));
				}
			}
		}
	}
};

int main() {
	int n, m, st, des;
	while (~scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		Graph g(n), gRev(n);
		scanf("%d%d", &st, &des);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			g.addEdge(a, b, c);
			gRev.addEdge(b, a, c);
		}
		g.dijkstra(st);
		gRev.dijkstra(des);
		int dist = g.d[des];
		if (dist == inf) {
			puts("-1");
			continue;
		}
		for (int u = 0; u < n; u++)
			for (vector<edge>::iterator it = g.adj[u].begin(); it != g.adj[u].end(); it++) {
				int v = it->v, w = it->w;
				if (g.d[u] + w + gRev.d[v] == dist) {
					it->mk = false;
				}
			}
		g.dijkstra(st);
		int ret = g.d[des];
		if (ret == inf) {
			puts("-1");
			continue;
		} else {
			printf("%d\n", ret);
		}
	}
	return 0;
}

