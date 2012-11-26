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
const int MAXN = 20005;
struct Graph {
	int n, depth;
	int dfn[MAXN], low[MAXN];
	bool udfs[MAXN], vis[MAXN];
	vector<int> adj[MAXN];

	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++)
			adj[i].clear();
		memset(dfn, -1, sizeof(dfn));
		memset(udfs, 0, sizeof(udfs));
		depth = 0;
	}

	void addEdge(int u, int v) {
		adj[u].PB(v);
	}

	bool Tarjan(int u) {
		dfn[u] = low[u] = depth++;
		vis[u] = true;
		int cnt = 0;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (udfs[v]) return false;
			if (dfn[v] == -1) {
				if (!Tarjan(v)) return false;
				if (low[v] > dfn[u]) return false;
				if (low[v] < dfn[u]) cnt++;
				if (cnt == 2) return false;
				low[u] = min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = min(low[u], dfn[v]);
				cnt++;
				if (cnt == 2) return false;
			}
		}
		udfs[u] = true;
		return true;
	}
}g;

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		int n;
		scanf("%d", &n);
		g.init(n);
		int u, v;
		while (scanf("%d%d", &u, &v) && u + v) {
			g.addEdge(u, v);
		}
		bool flag = g.Tarjan(u);
		if (flag) {
			for (int i = 0; i < n; i++)
				if (g.dfn[i] == -1) {
					flag = false;
					break;
				}
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
