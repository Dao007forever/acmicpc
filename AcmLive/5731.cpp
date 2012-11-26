/*
 * Author: Yang Zhang
 * Created Time: Thu 30 Aug 2012 07:58:53 PM CST
 * File Name: 5731.cpp
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
int n;
int f[MAXN], g[MAXN];
vector<pair<int, int> > adj[MAXN];

void addEdge(int u, int v, int d) {
	adj[u].PB(MP(v, d));
}

void dfs(int u, int fa, int dir) {
	f[u] = g[u] = 0;
	int up = 0, dn = 0;
	for (int i = 0, v; i < adj[u].size(); i++)
		if ((v = adj[u][i].first) != fa) {
			dfs(v, u, adj[u][i].second);
			if (adj[u][i].second) dn += max(1, g[v]);
			else up += max(1, g[v]);
			f[u] += f[v];
			if (!g[v]) f[u]++;
		}
	f[u] -= min(up, dn);
	if (dir) g[u] = max(0, dn - up);
	else g[u] = max(0, up - dn);
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) adj[i].clear();
		for (int i = 1; i < n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			addEdge(a, b, 0); addEdge(b, a, 1);
		}
		dfs(0, -1, 0);
		printf("Case %d: %d\n", cas, f[0]);
	}
	return 0;
}

