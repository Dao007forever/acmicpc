/*
 * 求树中到其他点距离最远的点最近的点（即树的中心）以及到其他点距离最远的点最远的点
 * 树形dp，先从下到上求出每个点经过儿子节点向下的最远距离和次远距离，然后再从上到下求出每个点经过父亲节点的最远距离，然后取最大值，转移的时候要判断它是否是它父亲向下的最远距离路径上的点
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

const int inf = 1000000000;
int N;
vector<int> ans[2];
vector<int> adj[5555];
int f[5555], g[5555];//通过儿子节点能够到达的最远和次远距离
int up[5555];//通过父亲节点能够到达的最远距离
int ret[5555];

void dfs1(int u, int fa) {
	f[u] = g[u] = 0;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v != fa) {
			dfs1(v, u);
			if (f[v] + 1 >= f[u]) {
				g[u] = f[u];
				f[u] = f[v] + 1;
			} else if (f[v] + 1 >= g[u]) {
				g[u] = f[v] + 1;
			}
		}
	}
}

void dfs2(int u, int fa) {
	up[u] = 0;
	if (fa) {
		if (f[u] == f[fa] - 1) {
			up[u] = max(g[fa], up[fa]) + 1;
		} else {
			up[u] = max(f[fa], up[fa]) + 1;
		}
	}
	ret[u] = max(f[u], up[u]);
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa)
			dfs2(adj[u][i], u);
}

int main() {
	freopen("in", "r", stdin);
	while (cin >> N) {
		for (int i = 1; i <= N; i++) {
			adj[i].clear();
			ret[i] = 0;
		}
		ans[0].clear(); ans[1].clear();
		for (int i = 1; i <= N; i++) {
			int x, j;
			cin >> x;
			while (x--) {
				cin >> j;
				adj[i].push_back(j);
			}
		}
		dfs1(1, 0);
		dfs2(1, 0);
		int Min = inf, Max = 0;
		for (int i = 1; i <= N; i++) {
			Min = min(ret[i], Min);
			Max = max(ret[i], Max);
		}
		for (int i = 1; i <= N; i++) {
			if (ret[i] == Min) ans[0].push_back(i);
			if (ret[i] == Max) ans[1].push_back(i);
		}
		printf("Best Roots  : ");
		for (int i = 0; i < ans[0].size(); i++)
			printf("%d%c", ans[0][i], i == ans[0].size() - 1 ? '\n' : ' ');
		printf("Worst Roots : ");
		for (int i = 0; i < ans[1].size(); i++)
			printf("%d%c", ans[1][i], i == ans[1].size() - 1 ? '\n' : ' ');
	}
	return 0;
}
