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
int dist[555];
vector<pair<int, int> > adj[555];
/*
 * Bellman_Ford
 */
bool Bellman_Ford() {
	memset(dist, 0, sizeof(dist));
	for (int i = 0; i < n; i++) {
		bool relaxed = false;
		for (int p = 0; p < n; p++)
			for (int j = 0; j < adj[p].size(); j++) {
				int q = adj[p][j].first, tmp = dist[p] + adj[p][j].second;
				if (dist[q] > tmp) {
					dist[q] = tmp;
					relaxed = true;
				}
			}
		if (!relaxed) return false;
	}
	return true;
}

int main() {
	freopen("in", "r", stdin);
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++)
			adj[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			adj[a].PB(MP(b, -c));
		}
		if (Bellman_Ford()) puts("n");
		else puts("y");
	}
	return 0;
}
