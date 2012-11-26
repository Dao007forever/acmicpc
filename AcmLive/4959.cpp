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

struct node {
	int mask;
	string path;
	node() {}
	node(int _mask, string _path) {
		mask = _mask;
		path = _path;
	}
};
int n, m;
int adj[22];
bool vis[1 << 21];
string ans;

bool bfs() {
	queue<node> Q;
	memset(vis, false, sizeof(vis));
	Q.push(node((1 << n) - 1, ""));
	vis[(1 << n) - 1] = true;
	while (!Q.empty()) {
		node cur = Q.front();
		Q.pop();
		for (int i = 0; i < n; i++)
			if (cur.mask & (1 << i)) {
				int mask = cur.mask ^ (1 << i);
				int newmask = 0;
				for (int j = 0; j < n; j++)
					if (mask & (1 << j)) newmask |= adj[j];
				if (vis[newmask]) continue;
				vis[newmask] = true;
				char ch = i + '0';
				string s = cur.path + ch;
				if (newmask == 0) {
					ans = s;
					return true;
				}
				Q.push(node(newmask, s));
			}
	}
	return false;
}

void solve() {
	if (m > n - 1 || !bfs()) puts("Impossible");
	else {
		printf("%d:", ans.size());
		for (int i = 0; i < ans.size(); i++)
			printf(" %d", ans[i] - '0');
		printf("\n");
	}
}

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &m) && n + m) {
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			adj[a] |= (1 << b);
			adj[b] |= (1 << a);
		}
		solve();
	}
	return 0;
}
