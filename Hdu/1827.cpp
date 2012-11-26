/*
 * Author: Yang Zhang
 * Created Time: Wed 29 Aug 2012 08:48:13 PM CST
 * File Name: 1827.cpp
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

int val[MAXN], minV[MAXN], deg[MAXN];
int main() {
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++)
			scanf("%d", &val[i]);
		g.init(n);
		for (; m--; ) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			g.addEdge(a, b);
		}
		g.SCC();
		for (int i = 1; i <= g.size; i++)
			minV[i] = 1000000000, deg[i] = 0;
		for (int i = 0; i < n; i++) {
			int id = g.id[i];
			minV[id] = min(minV[id], val[i]);
			for (int j = 0, v; j < g.adj[i].size(); j++) {
				if ((g.id[v = g.adj[i][j]]) != g.id[i]) {
					deg[g.id[v]]++;
				}
			}
		}
		int ret = 0, cnt = 0;
		for (int i = 1; i <= g.size; i++)
			if (deg[i] == 0) {
				cnt++;
				ret += minV[i];
			}
		printf("%d %d\n", cnt, ret);
	}
	return 0;
}

