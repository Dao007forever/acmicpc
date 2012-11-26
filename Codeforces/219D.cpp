/*
 * Author: Yang Zhang
 * Created Time: Wed 29 Aug 2012 02:48:39 PM CST
 * File Name: 219D.cpp
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

#define MAXN 200005
int n, E;
//int to[MAXN], prev[MAXN], dir[MAXN], last[MAXN];
int f[MAXN], g[MAXN];
vector<pair<int, int> > adj[MAXN];

void addEdge(int u, int v, int type) {
	adj[u].PB(MP(v, type));
//	to[E] = v; dir[E] = type; prev[E] = last[u]; last[u] = E; E++;
}

void dfs(int u, int fa) {
	/*for (int i = last[u], v; i != -1; i = prev[i]) {
		if ((v = to[i]) != fa) {
			dfs(v, u);
		}
	}
	f[u] = 0;
	for (int i = last[u], v; i != -1; i = prev[i]) {
		if ((v = to[i]) != fa) {
			f[u] += f[v];
			if (!dir[i]) f[u]++;
		}
	}*/
	for (int i = 0, v; i < adj[u].size(); i++) {
		if ((v = adj[u][i].first) != fa) {
			dfs(v, u);
		}
	}
	f[u] = 0;
	for (int i = 0, v; i < adj[u].size(); i++) {
		if ((v = adj[u][i].first) != fa) {
			f[u] += f[v];
			if (!adj[u][i].second) f[u]++;
		}
	}
}

void dfs_rev(int u, int fa) {
	/*for (int i = last[u], v; i != -1; i = prev[i]) {
		if ((v = to[i]) != fa) {
			g[v] += g[u];
			if (dir[i]) g[v]++;
			g[v] += f[u] - f[v];
			if (!dir[i]) g[v]--;
			dfs_rev(v, u);
		}
	}*/
	for (int i = 0, v; i < adj[u].size(); i++) {
		if ((v = adj[u][i].first) != fa) {
			g[v] += g[u];
			if (adj[u][i].second) g[v]++;
			g[v] += f[u] - f[v];
			if (!adj[u][i].second) g[v]--;
			dfs_rev(v, u);
		}
	}
}

int main() {
	E = 0;
	//memset(last, -1, sizeof(last));
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		addEdge(a, b, 1);
		addEdge(b, a, 0);
	}
	dfs(1, 0);
	dfs_rev(1, 0);
	int ret = 10000000;
	for (int i = 1; i <= n; i++)
		ret = min(ret, f[i] + g[i]);
	cout << ret << endl;
	bool flag = false;
	for (int i = 1; i <= n; i++) 
		if (f[i] + g[i] == ret) {
			if (flag) {
				cout << " ";
			}
			flag = true;
			cout << i;
		}
	cout << endl;
	return 0;
}

