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

#define MAXN 3001
const int inf = 1000000000;
int g[MAXN][MAXN], best[MAXN][MAXN], dis[MAXN], pre[MAXN];
bool vst[MAXN];
int n, m;
LL total;
vector<int> adj[MAXN];
struct node {
	int u, d;
	node(int _u, int _d) {
		u = _u; d = _d;
	}
	bool operator < (const node &it) const {
		return d > it.d;
	}
};

inline void init() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g[i][j] = best[i][j] = inf;
		}
		vst[i] = false;
		pre[i] = -1;
		dis[i] = inf;
		adj[i].clear();
	}
}

inline void input() {
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[u][v] = g[v][u] = w;
	}
}

inline void prim() {
	total = 0;
	dis[0] = 0;
	//priority_queue<node> Q;
	//Q.push(node(0, 0));
	for (int j = 0; j < n; j++) {
		//node cur = Q.top(); Q.pop();
		//int u = cur.u;
		int u = -1;
		for (int i = 0; i < n; i++)
			if (!vst[i] && (u == -1 || dis[i] < dis[u]))
				u = i;
		vst[u] = true;
		total += dis[u];
		if (pre[u] != -1) {
			adj[u].PB(pre[u]);
			adj[pre[u]].PB(u);
		}
		for (int i = 0; i < n; i++)
			if (!vst[i] && g[u][i] < dis[i]) {
				dis[i] = g[u][i];
				pre[i] = u;
				//Q.push(node(i, dis[i]));
			}
	}
}

inline int dfs(int st, int u, int fa) {
	int Min = inf;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v == fa) continue;
		int cur = dfs(st, v, u);
		Min = min(Min, cur);
		best[u][v] = best[v][u] = min(best[u][v], cur);
	}
	if (st != fa) Min = min(Min, g[st][u]);
	return Min;
}

inline void work() {
	for (int i = 0; i < n; i++)
		dfs(i, i, -1);
}

inline void query() {
	int q;
	scanf("%d", &q);
	LL ret = total * q;
	for (int i = 0; i < q; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if (pre[u] == v || pre[v] == u) {
			ret += min(w, best[u][v]) - g[u][v];
		}
	}
	printf("%.4f\n", (double)ret / q);
}

int main() {
	freopen("in.txt", "r", stdin);
	while (scanf("%d%d", &n, &m) && n + m) {
		init();
		input();
		prim();
		work();
		query();
	}
	return 0;
}
