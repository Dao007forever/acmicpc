/*
 * Author: Yang Zhang
 * Created Time: Sun 01 Jul 2012 03:19:37 PM UTC
 * File Name: main.cpp
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

const int MAXN = 200005;
const LL inf = 1LL << 60;
int n;
int X1, X2;
LL dis[MAXN];
bool vst[MAXN];
vector<pair<int, int> > adj[MAXN];

void addEdge(int u, int v, LL w) {
	adj[u].PB(MP(v, w));
}

void dijkstra() {
	for (int i = 0; i <= n; i++) {
		dis[i] = inf; vst[i] = false;
	}
	dis[n] = 0;
	priority_queue<pair<LL, int> > Q;
	Q.push(MP(0, n));
	int u, v;
	vector<pair<int, int> >::iterator it;
	while (!Q.empty()) {
		pair<LL, int> cur = Q.top(); Q.pop();
		u = cur.second;
		vst[u] = true;
		if (u == 0) break;
		for (it = adj[u].begin(); it != adj[u].end(); it++) {
			if (!vst[v = it->first]) {
				if (dis[u] + it->second < dis[v]) {
					dis[v] = dis[u] + it->second;
					Q.push(MP(-dis[v], v));
				}
			}
		}
	}
}

void solve() {
	dijkstra();
	if (dis[0] == inf) printf("Impossible\n");
	else printf("%lld\n", dis[0]);
}

void build() {
	for (int i = 0; i <= n; i++) {
		if (i >= 11) addEdge(i, i - 11, X1);
		if (i % 3 == 0) addEdge(i, i / 3 * 2, i / 3);
		if (i + 7 <= n) addEdge(i, i + 7, X2);
		if (2 * i + 1 <= n) addEdge(i, 2 * i + 1, i + 1);
	}
}

void init() {
	for (int i = 0; i <= n; i++)
		adj[i].clear();
}

int main() {
	while (scanf("%d%d%d", &n, &X1, &X2) && n && X1 && X2) {
		init();
		build();
		solve();
	}
	return 0;
}

