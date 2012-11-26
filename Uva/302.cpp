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

struct Edge {
	int v, id;

	bool operator < (const Edge &p) const {
		return id < p.id;
	}
};
int start;
int deg[2222], vis[2222];
vector<Edge> g[2222];
vector<int> ans;

bool check() {
	for (int i = 0; i < 45; i++)
		if (deg[i] && deg[i] & 1) return false;
	return true;
}

void Euler(int u) {
	for (int i = 0; i < g[u].size(); i++)
		if (!vis[g[u][i].id]) {
			int v = g[u][i].v;
			vis[g[u][i].id] = 1;
			Euler(v);
			ans.push_back(g[u][i].id);
		}
}

int main() {
	freopen("in", "r", stdin);
	int x, y, z;
	while (scanf("%d%d", &x, &y) && x && y) {
		memset(deg, 0, sizeof(deg));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < 45; i++)
			g[i].clear();
		ans.clear();
		start = 100;

		scanf("%d", &z);
		Edge tmp;
		tmp.v = y; tmp.id = z;
		g[x].push_back(tmp);
		tmp.v = x; tmp.id = z;
		g[y].push_back(tmp);
		deg[x]++; deg[y]++;
		start = min(x, y);
		while (scanf("%d%d", &x, &y) && x && y) {
			scanf("%d", &z);
			tmp.v = y; tmp.id = z;
			g[x].push_back(tmp);
			tmp.v = x; tmp.id = z;
			g[y].push_back(tmp);
			deg[x]++; deg[y]++;
		}
		if (!check()) {
			cout << "Round trip does not exist." << endl;
			cout << endl;
			continue;
		}
		for (int i = 0; i < 45; i++)
			if (deg[i]) {
				sort(g[i].begin(), g[i].end());
			}

		Euler(start);
		reverse(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); i++)
			printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
		cout << endl;
	}
	return 0;
}
