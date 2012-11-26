/*
 * Author: Yang Zhang
 * Created Time: Sun 26 Aug 2012 09:52:40 PM CST
 * File Name: 5538_BRHMAIL.cpp
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

int n;
int vis[15];
vector<int> adj[15];
void dfs(int u) {
	vis[u] = true;
	for (int i = 0; i < adj[u].size(); i++)
		if (!vis[adj[u][i]]) dfs(adj[u][i]);
}
int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i <= n; i++) adj[i].clear();
		for (int i = 1; i <= n; i++) {
			int k, x;
			scanf("%d", &k);
			while (k--) {
				scanf("%d", &x);
				adj[i].PB(x);
			}
		}
		memset(vis, 0, sizeof(vis));
		dfs(1);
		int ret = 0;
		for (int i = 1; i <= n; i++)
			if (vis[i]) ret++;
		printf("%d\n", ret);
	}
	return 0;
}

