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

#define MAXN 100005
#define MAXM 500005
int n, m, q, depth;
vector<pair<int, int> > adj[MAXN];
int dfn[MAXN], low[MAXN], leave[MAXN], deep[MAXN];
int fa[20][MAXN];
bool visit[MAXM];

void addEdge(int u, int v, int id) {
	adj[u].PB(MP(v, id));
}

void Tarjan(int u, int dep) {
	dfn[u] = low[u] = depth++;
	deep[u] = dep;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i].first, id = adj[u][i].second;
		if (dfn[v] == -1) {
			fa[1][v] = u;
			visit[id] = true;
			Tarjan(v, dep + 1);
			low[u] = min(low[u], low[v]);
		} else if (!visit[id]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	leave[u] = depth;
}

int move(int x, int step) {
	int t = x, p = 1;
	if (step < 0) return -1;
	for (; step; step >>= 1) {
		if (step & 1) t = fa[p][t];
		p++;
	}
	return t;
}

bool judgeEdge(int a, int b, int g1, int g2) {
	if (deep[g1] < deep[g2]) swap(g1, g2);
	int ina = 0, inb = 0;
	if (dfn[g1] <= dfn[a] && leave[a] <= leave[g1]) {
		ina = 1;
	}
	if (dfn[g1] <= dfn[b] && leave[b] <= leave[g1]) {
		inb = 1;
	}
	if ((ina && inb) || (!ina && !inb)) {
		return true;
	} else {
		if (low[g1] <= dfn[g2]) {
			return true;
		} else {
			return false;
		}
	}
}

bool judgeVertex(int a, int b, int g1) {
	int ina = 0, inb = 0;
	if (dfn[g1] <= dfn[a] && leave[a] <= leave[g1]) {
		ina = 1;
	}
	if (dfn[g1] <= dfn[b] && leave[b] <= leave[g1]) {
		inb = 1;
	}
	if (!ina && !inb) return true;
	if (ina && !inb) {
		int t = move(a, deep[a] - deep[g1] - 1);
		if (low[t] < dfn[g1]) return true;
	}
	if (!ina && inb) {
		int t = move(b, deep[b] - deep[g1] - 1);
		if (low[t] < dfn[g1]) return true;
	}
	int t1 = move(a, deep[a] - deep[g1] - 1);
	int t2 = move(b, deep[b] - deep[g1] - 1);
	if (t1 == t2) return true;
	if (low[t1] < dfn[g1] && low[t2] < dfn[g1]) return true;
	return false;
}

void solve() {
	depth = 0;
	for (int i = 0; i < n; i++) dfn[i] = -1;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < n; j++)
			fa[i][j] = -1;
	for (int i = 0; i < n; i++) {
		if (dfn[i] == -1) {
			Tarjan(i, 0);
		}
	}
	for (int i = 2; i < 20; i++)
		for (int j = 0; j < n; j++)
			if (fa[i - 1][j] != -1) {
				fa[i][j] = fa[i - 1][fa[i - 1][j]];
			}

	scanf("%d", &q);
	while (q--) {
		int type;
		int a, b, g1, g2;
		scanf("%d", &type);
		if (type == 1) {
			scanf("%d%d%d%d", &a, &b, &g1, &g2);
			a--; b--; g1--; g2--;
			bool flag = judgeEdge(a, b, g1, g2);
			if (flag) puts("yes");
			else puts("no");
		} else {
			scanf("%d%d%d", &a, &b, &g1);
			a--; b--; g1--;
			bool flag = judgeVertex(a, b, g1);
			if (flag) puts("yes");
			else puts("no");
		}
	}
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d", &n, &m)) {
		memset(visit, 0, sizeof(visit));
		for (int i = 0; i < n; i++) adj[i].clear();
		for (int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			addEdge(a, b, i);
			addEdge(b, a, i);
		}
		solve();
	}
	return 0;
}