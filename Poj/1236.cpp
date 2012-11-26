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

#define MAXN 105
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
		g.init(n);
		for (int i = 0; i < n; i++) {
			int x;
			while (scanf("%d", &x) && x) {
				x--;
				g.addEdge(i, x);
			}
		}
		g.SCC();
		std::vector<int> indeg(g.size + 1), outdeg(g.size + 1);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < g.adj[i].size(); j++) {
				if (g.id[i] != g.id[g.adj[i][j]]) {
					outdeg[g.id[i]]++;
					indeg[g.id[g.adj[i][j]]]++;
				}
			}
		int r1 = 0, r2 = 0;
		for (int i = 1; i <= g.size; i++) {
			r1 += indeg[i] == 0;
			r2 += outdeg[i] == 0;
		}
		printf("%d\n", r1);
		if (g.size == 1) printf("0\n");
		else printf("%d\n", max(r1, r2));
	}
	return 0;
}