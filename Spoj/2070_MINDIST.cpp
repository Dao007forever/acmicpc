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

#define MAXN 100005
const int inf = 1000000000;
int N;
vector<pair<int, int> > adj[MAXN];
int f[MAXN], g[MAXN];//通过儿子节点能够到达的最远和次远距离
int up[MAXN];//通过父亲节点能够到达的最远距离
int N, S;

void dfs1(int u, int fa) {
	f[u] = g[u] = 0;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i].first, w = adj[u][i].second;
		if (v != fa) {
			dfs1(v, u);
			if (f[v] + w >= f[u]) {
				g[u] = f[u];
				f[u] = f[v] + w;
			} else if (f[v] + w >= g[u]) {
				g[u] = f[v] + w;
			}
		}
	}
}

void dfs2(int u, int len, int fa) {
	up[u] = 0;
	if (fa) {
		if (f[u] == f[fa] - len) {
			up[u] = max(g[fa], up[fa]) + len;
		} else {
			up[u] = max(f[fa], up[fa]) + len;
		}
	}
	ret[u] = max(f[u], up[u]);
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i].first != fa)
			dfs2(adj[u][i].first, adj[u][i].second, u);
}

bool check(int u, int fa) {
	int cnt = 0;
	minl[u] = -1;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i].first;
		if (v != fa) {
			if (check(v, u)) return true;

			int delta = minl[v] + adj[u][i].second;
			if (f[v] + adj[u][i].second <= lim) delta = 0;
			else {
				cnt++;
				minl[u] = delta;
			}
		}
	}
}

int main() {
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> N >> S;
		for (int i = 1; i <= N; i++)
			adj[i].clear();
		for (int i = 1; i < N; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			adj[a].PB(MP(b, c));
			adj[b].PB(MP(a, c));
		}

		dfs1(1, 0);
		dfs2(1, 0, 0);

		int l = -1, r = N * 1000;
		while (r - l > 1) {
			int mid = (l + r) >> 1;
			lim = mi;
			if (check(1, 0)) r = mid;
			else l = mid;
		}
		printf("%d\n", r);
	}
	return 0;
}
