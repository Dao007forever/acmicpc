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

const int maxn = 100005;
struct Graph {
	int n, size, depth;
	vector<int> adj[maxn];
	int low[maxn], dfn[maxn], id[maxn];
	bool vis[maxn];
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

struct Edge {
	int u, v, w;
	int idx;
	Edge() {}
	Edge(int u, int v, int w, int idx) : u(u), v(v), w(w), idx(idx) {}
}edge[maxn];
vector<pair<int, int> > graph[maxn];
bool vis[maxn];
int deg[maxn];
vector<int> ans;

int main(int argc, char const *argv[])
{
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> edge[i].u >> edge[i].v >> edge[i].w;
		edge[i].u--; edge[i].v--; edge[i].idx = i + 1;
	}
	g.init(n);
	for (int i = 0; i < m; i++) {
		if (edge[i].w == 0) {
			g.addEdge(edge[i].u, edge[i].v);
		}
	}
	g.SCC();
	int size = g.size;
	memset(deg, 0, sizeof(deg));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < m; i++) {
		if (edge[i].w == 1) continue;
		int a = g.id[edge[i].u], b = g.id[edge[i].v];
		if (a != b) {
			deg[b]++;
			graph[a].PB(MP(b, 0));
		}
	}
	for (int i = 0; i < m; i++) {
		if (edge[i].w == 0) continue;
		int a = g.id[edge[i].u], b = g.id[edge[i].v];
		if (a != b && !deg[b]) {
			graph[a].PB(MP(b, edge[i].idx));
		}
	}
	ans.clear();
	queue<int> q;
	q.push(g.id[0]);
	vis[g.id[0]] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < graph[u].size(); i++) {
			int v = graph[u][i].first, idx = graph[u][i].second;
			if (!vis[v]) {
				vis[v] = true;
				q.push(v);
				if (idx) ans.PB(idx);
			}
		}
	}
	bool flag = true;
	for (int i = 1; i <= size; i++) {
		if (!vis[i]) {
			flag = false;
			break;
		}
	}
	if (!flag) {
		cout << -1 << endl;
	} else {
		cout << ans.size() << endl;
		for (int i = 0; i < ans.size(); i++)
			printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	}
	return 0;
}