/*
 * Author: Yang Zhang
 * Created Time: Mon 17 Sep 2012 10:22:39 AM CST
 * File Name: 3413_SAMER08I.cpp
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

#define MAXN 505
int n, c;
int deg[101];
int g[101][101];
bool vis[101];
vector<int> city[505];

void dfs(int u) {
	vis[u] = true;
	for (int i = 0; i < c; i++)
		if (!vis[i] && g[u][i]) dfs(i);
}

bool connect() {
	memset(vis, 0, sizeof(vis));
	int cnt = 0;
	for (int i = 0; i < c; i++)
		if (deg[i]) {
			if (!vis[i]) {
				if (cnt == 0) {
					dfs(i);
					cnt++;
				} else return false;
			}
		}
	return true;
}

int solve() {
	if (!connect()) {
		return -1;
	}
	int odd = 0;
	for (int i = 0; i < c; i++)
		if (deg[i] & 1) odd++;
	if (odd == 0) return 0; // euler circuit
	if (odd != 2) return -1; // no euler path

	//find euler path, start with Vertex i
	for (int i = 0; i < n; i++) {
		int c1 = city[i][0], c2 = city[i][1];
		if (deg[c1] % 2 == 0 && deg[c2] % 2 == 0) continue;
		deg[c1]--; deg[c2]--;
		g[c1][c2]--; g[c2][c1]--;
		if (connect()) return i;
		g[c1][c2]++; g[c2][c1]++;
		deg[c1]++; deg[c2]++;
	}
	return -1;
}

int main() {
	while (~scanf("%d%d", &n, &c)) {
		if (n == 0 && c == 0) break;
		memset(g, 0, sizeof(g));
		for (int i = 0; i < n; i++) city[i].clear();
		for (int i = 0; i < c; i++) {
			scanf("%d", &deg[i]);
			for (int j = 0; j < deg[i]; j++) {
				int x;
				scanf("%d", &x);
				city[x].PB(i);
			}
		}
		for (int i = 0; i < n; i++) {
			if (SZ(city[i]) == 1) {
				city[i].PB(city[i][0]);
				deg[city[i][0]]++;
			} else {
				g[city[i][0]][city[i][1]]++;
				g[city[i][1]][city[i][0]]++;
			}
		}
		int ret = solve();
		printf("%d\n", ret);
	}
	return 0;
}

