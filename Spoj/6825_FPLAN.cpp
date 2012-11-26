/*
 * Author: Yang Zhang
 * Created Time: Fri 24 Aug 2012 01:26:23 PM CST
 * File Name: 6825_FPLAN.cpp
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
#define MAXN 100005
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

struct DisJointSet{
	int rank[MAXN], parent[MAXN];

	void init(int n) {
		for (int i = 0; i <= n; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}
	int count(int n) {
		int ret = 0;
		for (int i = 0; i < n; i++)
			if (parent[i] == i) ret++;
		return ret;
	}
}dsu;

int n, m;
int indeg[MAXN];
int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		scanf("%d%d", &n, &m);
		g.init(n);
		dsu.init(n);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			g.addEdge(a, b);
			int pa = dsu.Find(a), pb = dsu.Find(b);
			if (pa != pb) dsu.Union(pa, pb);
		}
		if (dsu.count(n) != 1) {
			puts("Confused");
			puts("");
			continue;
		}
		g.SCC();
		memset(indeg, 0, sizeof(indeg));
		for (int u = 0; u < n; u++)
			for (int i = 0; i < g.adj[u].size(); i++) {
				int v = g.adj[u][i];
				if (g.id[u] != g.id[v]) {
					indeg[g.id[v]]++;
				}
			}
		int cnt_deg = 0, idx;
		for (int i = 1; i <= g.size; i++)
			if (indeg[i] == 0) {
				idx = i;
				cnt_deg++;
			}
		if (cnt_deg != 1) {
			puts("Confused");
			puts("");
			continue;
		}
		for (int i = 0; i < n; i++)
			if (g.id[i] == idx) {
				printf("%d\n", i);
			}
		puts("");
	}
}

