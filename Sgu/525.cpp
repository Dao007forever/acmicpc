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

int n, m;
vector<int> adj[1005], ans[1005], r;
vector<pair<int, int> > edge;
bool reach[1005][1005];
bool vis[1005];

void dfs(int s, int u) {
	reach[s][u] = true;
	vis[u] = true;
	for (int i = 0; i < adj[u].size(); i++)
		if (!vis[adj[u][i]]) dfs(s, adj[u][i]);
}

int main() {
	freopen("in", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		edge.PB(MP(a, b));
		adj[a].PB(b);
	}

	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		dfs(i, i);
	}
	
	int ret = 0;
	for (int k = 0; k < m; k++) {
		int a = edge[k].first, b = edge[k].second;
		int cnt = 2;
		for (int i = 1; i <= n; i++)
			if (i != a && i != b && reach[a][i] && reach[i][b]) {
				cnt++;
			}
		if (cnt >= 2) {
			ans[cnt].PB(k + 1);
			ret = max(ret, cnt);
		}
	}
	if (ret) {
		cout << ret << endl;
		cout << ans[ret].size() << endl;
		for (int i = 0; i < ans[ret].size(); i++)
			printf("%d%c", ans[ret][i], i == ans[ret].size() - 1 ? '\n' : ' ');
	} else {
		cout << 1 << endl;
		cout << 0 << endl;
	}
	return 0;
}

