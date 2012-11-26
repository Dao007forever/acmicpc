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

#define MAXN 20005
struct Graph {
	int n, depth, size;
	int dfn[555], low[555], id[555];
	bool vis[555];
	vector<int> adj[555];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= 2 * n; i++)
			adj[i].clear();
		memset(dfn, -1, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(vis, false, sizeof(vis));
		memset(id, 0, sizeof(id));
		while (!S.empty()) S.pop();
	}

	void addEdge(int a, int b) {
		adj[a].PB(b);
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

	bool twosat() {
		depth = 1; size = 0;
		for (int i = 0; i < 2 * n; i++)
			if (dfn[i] == -1) Tarjan(i);
		for (int i = 0; i < n; i++)
			if (id[i] == id[i + n]) return false;
		return true;
	}

}g;
int n, m;
int a[MAXN], b[MAXN], c[MAXN];

bool check(int lim) {
	g.init(n);
	for (int i = 1; i <= lim; i++) {
		if (c[i] == 0) {
			//xai==0, xbi==0
			g.addEdge(a[i], b[i] + n);
			g.addEdge(b[i], a[i] + n);
		} else if (c[i] == 1) {
			//xai==0, xbi==1
			g.addEdge(a[i], b[i]);
			g.addEdge(b[i] + n, a[i] + n);
			//xai==1, xbi==0
			g.addEdge(a[i] + n, b[i] + n);
			g.addEdge(b[i], a[i]);
		} else if (c[i] == 2) {
			//xai==1, xbi==1
			g.addEdge(a[i] + n, b[i]);
			g.addEdge(b[i] + n, a[i]);
		}
	}
	int flag = g.twosat();
	return flag;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++)
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
		int l = 0, r = m, ret;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				ret = mid;
				l = mid + 1;
			} else r = mid - 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
