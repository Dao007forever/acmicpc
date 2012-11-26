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

#define MAXN 2005
struct Graph {
	int n;
	int ind[MAXN], ans[MAXN];
	vector<int> adj[MAXN];
	vector<int> topo;

	void init(int n) {
		this->n = n;
		memset(ind, 0, sizeof(ind));
		memset(ans, 0, sizeof(ans));
		topo.clear();
		for (int i = 1; i <= n; i++)
			adj[i].clear();
	}

	void addEdge(int u, int v) {
		adj[u].PB(v);
		ind[v]++;
	}

	bool toposort() {
		queue<int> Q;
		for (int cnt = 0; cnt < n; ) {
			int k = 0;
			for (int i = 1; i <= n; i++) {
				if (ind[i] == 0) {
					Q.push(i);
					k++;
				}
			}
			if (k == 0) {
				return false;
			}
			while (!Q.empty()) {
				int u = Q.front();
				Q.pop();
				topo.PB(u);
				ind[u] = -1;
				for (int i = 0; i < adj[u].size(); i++)
					ind[adj[u][i]]--;
			}
			cnt += k;
		}
		return true;
	}

	void output() {
		for (int i = 0; i < topo.size(); i++)
			ans[topo[i]] = i + 1;
	}
}g[3];

int n, m;

int main() {
	freopen("in", "r", stdin);
	int cas = 1;
	while (scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		printf("Case %d: ", cas++);
		for (int i = 0; i < 3; i++)
			g[i].init(2 * n);
		for (int i = 0; i < 3; i++)
			for (int j = 1; j <= 2 * n; j++)
				g[i].addEdge(j, j + n);
		while (m--) {
			char op[5];
			int a, b;
			scanf("%s%d%d", op, &a, &b);
			if (*op == 'I') {
				for (int i = 0; i < 3; i++) {
					g[i].addEdge(a, b + n);
					g[i].addEdge(b, a + n);
				}
			} else {
				int t = *op - 'X';
				g[t].addEdge(a + n, b);
			}
		}
		bool b[3];
		for (int i = 0; i < 3; i++)
			b[i] = g[i].toposort();
		if (!b[0] || !b[1] || !b[2]) {
			printf("IMPOSSIBLE\n");
		} else {
			printf("POSSIBLE\n");
			for (int i = 0; i < 3; i++) {
				g[i].output();
			}
			for (int i = 1; i <= n; i++)
				printf("%d %d %d %d %d %d\n", g[0].ans[i], g[1].ans[i], g[2].ans[i], g[0].ans[i + n], g[1].ans[i + n], g[2].ans[i + n]);
		}
		puts("");
	}
	return 0;
}
