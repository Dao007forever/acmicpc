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

#define MAXN 1005
const int inf = 1000000000;
struct Graph {
	int n, m;
	int cnt[MAXN], dis[MAXN];
	bool vis[MAXN];
	vector<pair<int, int> > adj[MAXN];

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
	}

	void addEdge(int u, int v, int w) {
		adj[u].PB(MP(v, w));
		//cout << u << " " << v << " " << w << endl;
	}

	/*int spfa() {
		for (int i = 0; i <= n; i++) {
			dis[i] = inf;
			vis[i] = false;
			cnt[i] = 0;
		}
		dis[0] = 0; vis[0] = true;
		cnt[0]++;
		queue<int> Q;
		Q.push(0);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			vis[u] = false;
			for (int i = 0; i < adj[u].size(); i++) {
				int v = adj[u][i].first, w = adj[u][i].second;
				if (dis[u] + w < dis[v]) {
					dis[v] = dis[u] + w;
					if (!vis[v]) {
						cnt[v]++;
						if (cnt[v] > n) return -inf;
						vis[v] = true;
						Q.push(v);
					}
				}
			}
		}
		return dis[n - 1];
	}*/

	bool Bellman_Ford() {
		for (int i = 0; i <= n; i++)
			dis[i] = inf;
		dis[0] = 0;
		for (int i = 0; i < n; i++) {
			for (int p = 0; p < n; p++)
				for (int j = 0; j < adj[p].size(); j++) {
					int q = adj[p][j].first, tmp = dis[p] + adj[p][j].second;
					if (dis[p] != inf && dis[q] > tmp) {
						dis[q] = tmp;
					}
				}
		}
		for (int p = 0; p < n; p++)
			for (int j = 0; j < adj[p].size(); j++) {
				int q = adj[p][j].first, tmp = dis[p] + adj[p][j].second;
				if (dis[p] != inf && dis[q] > tmp) return false;
			}
		return true;
	}
}g;

int n, m;
int mat[33][33];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

bool check(int x, int y) {
	if (x >= 0 && x < n && y >= 0 && y < m && mat[x][y] != 1) return true;
	return false;
}

int main() {
//	freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &m) && n + m) {
		g.init(n * m);
		memset(mat, 0, sizeof(mat));
		int t;
		scanf("%d", &t);
		for (int i = 0; i < t; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			mat[a][b] = 1;
		}
		scanf("%d", &t);
		for (int i = 0; i < t; i++) {
			int X1, X2, Y1, Y2, time;
			scanf("%d%d%d%d%d", &X1, &Y1, &X2, &Y2, &time);
			mat[X1][Y1] = 2;
			g.addEdge(m * X1 + Y1, m * X2 + Y2, time);
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (!mat[i][j]) {
					if (i == n - 1 && j == m - 1) continue;
					for (int k = 0; k < 4; k++) {
						int x = i + dx[k], y = j + dy[k];
						if (check(x, y)) 
							g.addEdge(m * i + j, m * x + y, 1);
					}
				}
		/*int ret = g.spfa();
		if (ret == -inf) puts("Never");
		else if (ret == inf) puts("Impossible");
		else printf("%d\n", ret);*/
		bool ret = g.Bellman_Ford();
		if (!ret) puts("Never");
		else {
			if (g.dis[g.n - 1] == inf) printf("Impossible\n");
			else printf("%d\n", g.dis[g.n - 1]);
		}
	}
	return 0;
}
