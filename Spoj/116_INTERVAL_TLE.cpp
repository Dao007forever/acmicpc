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

#define MAXN 50005
const int inf = 100000000;
int n, minV, maxV;
int dist[MAXN];
vector<pair<int, int> > adj[MAXN];
//vector<pair<int, int> > edge;
//vector<int> cost;

void addEdge(int u, int v, int w) {
	adj[u].PB(MP(v, w));
	//cout << u << " " << v << " " << w << endl;
}

bool Bellman_Ford() {
	int nodes = maxV - minV;
	for (int i = minV; i <= maxV; i++)
		dist[i] = inf;
	dist[maxV] = 0;
	for (int i = 0; i <= nodes; i++) {
		bool relaxed = false;
		for (int p = minV; p <= maxV; p++)
			for (int j = 0; j < adj[p].size(); j++) {
				int q = adj[p][j].first, tmp = dist[p] + adj[p][j].second;
				if (tmp < dist[q]) {
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
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> n;
		for (int i = 0; i < MAXN - 4; i++)
			adj[i].clear();
		minV = MAXN;
		maxV = 0;
		while (n--) {
			int a, b, c;
			cin >> a >> b >> c;
			minV = min(minV, a);
			maxV = max(maxV, b + 1);
			addEdge(b + 1, a, -c);
		}

		for (int i = minV; i < maxV; i++) {
			addEdge(i + 1, i, 0);
			addEdge(i, i + 1, 1);
		}
		Bellman_Ford();
		cout << -dist[minV] << endl;
	}
	return 0;
}
