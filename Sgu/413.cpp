/*
 * Author: Yang Zhang
 * Created Time: Tue 28 Aug 2012 06:35:56 PM CST
 * File Name: 410.cpp
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

#define MAXN 105
int n, m, cnt;
vector<int> adj[MAXN], part[MAXN];
int col[MAXN], vis[MAXN];

void dfs(int u) {
	vis[u] = true;
	part[u].clear();
	for (int i = 0, v; i < adj[u].size(); i++) {
		if (!vis[v = adj[u][i]]) {
			dfs(v);
			if (col[v] == 0) {
				part[u].PB(v);
			}
		}
	}
	if (part[u].size() > 0) {
		cnt++;
		col[u] = cnt;
		for (int i = 0; i < part[u].size(); i++) {
			col[part[u][i]] = cnt;
		}
	}
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i <= n; i++) adj[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			adj[a].PB(b); adj[b].PB(a);
		}
		if (n == 1) {
			puts("1\n");
			continue;
		}
		for (int i = 1; i <= n; i++) {
			memset(col, 0, sizeof(col));
			memset(vis, 0, sizeof(vis));
			cnt = 0;
			dfs(i);
			if (col[i]) {
				for (int i = 1; i <= n; i++)
					printf("%d%c", col[i], i == n ? '\n' : ' ');
				break;
			}
		}
	}
	return 0;
}

