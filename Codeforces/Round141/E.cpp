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

#define MAXN 205
struct Graph {
	int n, depth, size;
	int dfn[MAXN], low[MAXN], id[MAXN];
	bool vis[MAXN];
	vector<int> adj[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= 2 * n; i++)
			adj[i].clear();
		memset(dfn, -1, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(vis, false, sizeof(vis));
		memset(id, 0, sizeof(id));
		while (!S.empty()) S.pop();
	}

	void addEdge(int a, int b) {
		adj[a].PB(b);
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

	bool twosat() {
		depth = 1; size = 0;
		for (int i = 0; i < 2 * n; i++)
			if (dfn[i] == -1) Tarjan(i);
		for (int i = 0; i < n; i++)
			if (id[i] == id[i + n]) return false;
		return true;
	}

	void output() {
		int cnt = 0;
		vector<int> vis(n);
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				vis[i] = 1; cnt++;
				for (int j = i + 1; j < n; j++) {
					if (id[j] == id[i]) {
						vis[j] = 1; cnt++;
					}
					if (id[j + n] == id[i]) {
						vis[j] = 2;
					}
				}
			}
		}
		cout << cnt << endl;
		for (int i = 0; i < n; i++)
			if (vis[i] & 1) cout << i + 1 << " ";
		cout << endl;
	}
}g;

int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	g.init(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		if (c == 1) {
			g.addEdge(a, b); g.addEdge(b, a);
			g.addEdge(a + n, b + n); g.addEdge(b + n, a + n);
		} else {
			g.addEdge(a, b + n); g.addEdge(b + n, a);
			g.addEdge(b, a + n); g.addEdge(a + n, b);
		}
	}
	bool flag = g.twosat();
	if (!flag) {
		puts("Impossible");
	} else {
		g.output();
	}
	return 0;
}