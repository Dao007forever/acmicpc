/*
 * 记忆化搜索
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

const int maxn = 20000;
int n;
vector<int> adj[maxn];
int deg[maxn], f[maxn];

int dfs(int u) {
	if (f[u] != -1) return f[u];
	f[u] = 0;
	for (int i = 0; i < adj[u].size(); i++)
		f[u] += dfs(adj[u][i]);
	return f[u];
}

int main() {
	freopen("in", "r", stdin);
	int blank = 0;
	while (cin >> n) {
		if (blank) puts("");
		blank = 1;
		for (int i = 0; i < n; i++)
			adj[i].clear();
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			deg[i] = x;
			while (x--) {
				int u;
				cin >> u;
				adj[u].push_back(i);
			}
		}
		memset(f, -1, sizeof(f));
		f[0] = 1;
		int ret = 0;
		for (int i = 1; i < n; i++)
			if (deg[i] == 0) ret += dfs(i);
		cout << ret << endl;
	}
	return 0;
}
