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
int adj[222][222], d[222];
vector<pair<int, int> > edge;

int bfs(int u) {
	memset(d, -1, sizeof(d));
	queue<int> Q;
	Q.push(u);
	d[u] = 0;
	int Max = 0, ret = u;
	while (!Q.empty()) {
		u = Q.front();
		Q.pop();
		for (int i = 1; i <= n; i++)
			if (adj[u][i] && d[i] == -1) {
				d[i] = d[u] + 1;
				Q.push(i);
				if (d[i] > Max) {
					Max = d[i];
					ret = i;
				}
			}
	}
	return ret;
}

int solve(int u) {
	int v = bfs(u);
	u = bfs(v);
	return d[u];
}

int main() {
	freopen("in", "r", stdin);
	memset(adj, 0, sizeof(adj));
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a][b] = adj[b][a] = 1;
		edge.PB(MP(a, b));
	}

	int ret = 0;
	for (int i = 0; i < edge.size(); i++) {
		int a = edge[i].first, b = edge[i].second;
		adj[a][b] = adj[b][a] = 0;
		int l1 = solve(a);
		int l2 = solve(b);
		ret = max(ret, l1 * l2);
		adj[a][b] = adj[b][a] = 1;
	}
	cout << ret << endl;
	return 0;
}
