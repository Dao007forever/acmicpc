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
/*------------#include omitted-----------*/
#define MAXN 1005
const int inf = 100000000;
struct Graph {
	int n;
	vector<pair<int, int> > adj[MAXN];
	int dis[MAXN];

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
	}

	void addEdge(int u, int v, int w) {
		adj[u].PB(MP(v, w));
	}

	bool bellman_ford(int st) {
		for (int i = 0; i <= n; i++)
			dis[i] = inf;
		dis[st] = 0;
		for (int i = 0; i < n; i++) {
			for (int p = 1; p <= n; p++)
				for (int j = 0; j < adj[p].size(); j++) {
					int v = adj[p][j].first, tmp = dis[p] + adj[p][j].second;
					if (tmp < dis[v]) {
						dis[v] = tmp;
					}
				}
		}
		for (int p = 1; p <= n; p++)
			for (int j = 0; j < adj[p].size(); j++) {
				int v = adj[p][j].first, tmp = dis[p] + adj[p][j].second;
				if (tmp < dis[v]) return false;
			}
		return true;
	}
}g;

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		int n, X, Y;
		scanf("%d%d%d", &n, &X, &Y);
		g.init(n);
		while (X--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			g.addEdge(u, v, w);
		}
		while (Y--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			g.addEdge(v, u, -w);
		}
		bool ret = g.bellman_ford(1);
		if (!ret) printf("-1\n");
		else {
			if (g.dis[n] == inf) printf("-2\n");
			else printf("%d\n", g.dis[n]);
		}
	}
	return 0;
}
