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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 4005
struct Graph {
	int n, size, depth;
	vector<int> adj[MAXN];
	int low[MAXN], dfn[MAXN], id[MAXN];
	bool vis[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
		memset(id, 0, sizeof(id));
		memset(vis, 0, sizeof(vis));
		while (!S.empty()) S.pop();
	}

	void addEdge(int u, int v) {
		adj[u].PB(v);
	}

	void Tarjan(int u) {
		dfn[u] = low[u] = depth++;
		S.push(u);
		vis[u] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dfn[v] == -1) {
				Tarjan(v);
				low[u] = min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			size++;
			int v;
			do {
				v = S.top();
				S.pop();
				id[v] = size;
				vis[v] = false;
			} while (u != v);
		}
	}

	void SCC() {
		memset(dfn, -1, sizeof(dfn));
		size = 0;
		depth = 1;
		for (int i = 0; i < n; i++)
			if (dfn[i] == -1) Tarjan(i);
	}

}g;

int main(int argc, char const *argv[])
{
	int n;
	while (~scanf("%d", &n)) {
		std::vector<int> v[n];
		g.init(2*n);
		for (int i = 0; i < n; i++) {
			int k, x;
			scanf("%d", &k);
			while (k--) {
				scanf("%d", &x);
				v[i].PB(x);
				g.addEdge(i, n + x - 1);
			}
		}
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d", &x);
			g.addEdge(n + x - 1, i);
		}
		g.SCC();
		for (int i = 0; i < n; i++) {
			std::vector<int> ans;
			for (int j = 0; j < v[i].size(); j++) {
				if (g.id[i] == g.id[n + v[i][j] - 1]) {
					ans.PB(v[i][j]);
				}
			}
			sort(ans.begin(), ans.end());
			printf("%d", ans.size());
			for (int i = 0; i < ans.size(); i++)
				printf(" %d", ans[i]);
			printf("\n");
		}
	}
	return 0;
}