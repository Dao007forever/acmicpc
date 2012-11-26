/*
 * Author: Yang Zhang
 * Created Time: Mon 17 Sep 2012 09:28:13 PM CST
 * File Name: 2375.cpp
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

#define MAXN 250005
struct Graph {
	int n, size, depth;
	//vector<int> adj[MAXN];
	int low[MAXN], dfn[MAXN], id[MAXN];
	bool vis[MAXN];

	int E;
	int to[MAXN << 3], prev[MAXN << 3];
	int last[MAXN];

	stack<int> S;

	void init(int n) {
		this->n = n;
		//for (int i = 0; i <= n; i++)
		//	adj[i].clear();
		E = 0;
		memset(last, -1, sizeof(last));
		memset(id, 0, sizeof(id));
		memset(vis, 0, sizeof(vis));
		while (!S.empty()) S.pop();
	}

	void addEdge(int u, int v) {
		to[E] = v; prev[E] = last[u]; last[u] = E++;
		//adj[u].PB(v);
	}

	void Tarjan(int u) {
		dfn[u] = low[u] = depth++;
		S.push(u);
		vis[u] = true;
		/*for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dfn[v] == -1) {
				Tarjan(v);
				low[u] = min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}*/
		for (int i = last[u]; ~i; i = prev[i]) {
			int v = to[i];
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
int h[505][505];
int ind[MAXN], outd[MAXN];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int id(int i, int j) {
	return i * m + j;
}
int main() {
	while (~scanf("%d%d", &m, &n)) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &h[i][j]);
		g.init(n*m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k], y = j + dy[k];
					if (x >= 0 && x < n && y >= 0 && y < m) {
						if (h[i][j] >= h[x][y]) {
							g.addEdge(id(i, j), id(x, y));
						}
					}
				}
			}
		g.SCC();
		if (g.size == 1) {
			puts("0");
		} else {
			/*vector<int> outd(g.size + 1), ind(g.size + 1);
			for (int u = 0; u < n * m; u++)
				for (vector<int>::iterator it = g.adj[u].begin(); it != g.adj[u].end(); it++) {
					if (g.id[u] != g.id[*it]) {
						outd[g.id[u]]++;
						ind[g.id[*it]]++;
					}
				}*/
			for (int i = 1; i <= g.size; i++) ind[i] = outd[i] = 0;
			for (int u = 0; u < n*m; u++)
				for (int i = g.last[u]; ~i; i = g.prev[i]) {
					int v = g.to[i];
					if (g.id[u] != g.id[v]) {
						outd[g.id[u]]++; ind[g.id[v]]++;
					}
				}
			int t1 = 0, t2 = 0;
			for (int i = 1; i <= g.size; i++) {
				t1 += (ind[i] == 0);
				t2 += (outd[i] == 0);
			}
			printf("%d\n", max(t1, t2));
		}
	}
	return 0;
}

