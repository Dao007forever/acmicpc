/*
 * Author: Yang Zhang
 * Created Time: Sat 08 Sep 2012 02:12:22 PM CST
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

int N, T;
bool vis[105][505];
int d[105][505], cost[105];
vector<pair<int, int> > adj[105];

void addEdge(int u, int v, int w) {
	adj[u].PB(MP(v, w));
}

void spfa(int st) {
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= T; j++)
			d[i][j] = -1, vis[i][j] = false;
	d[st][0] = 0;
	queue<pair<int, int> > q;
	q.push(MP(st, 0));
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		int u = cur.first, t = cur.second;
		vis[u][t] = false;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, w = adj[u][i].second;
			if (t + w <= T && (d[v][t + w] == -1 || d[u][t] + cost[v] > d[v][t + w])) {
				d[v][t + w] = d[u][t] + cost[v];
				if (!vis[v][t + w]) {
					vis[v][t + w] = true;
					q.push(MP(v, t + w));
				}
			}
		}
	}
	int ret = -1;
	for (int i = 0; i <= T; i++)
		if (d[N][i] > ret) {
			ret = d[N][i];
		}
	if (ret == -1) {
		puts("Human beings die in pursuit of wealth, and birds die in pursuit of food!");
	} else {
		printf("%d\n", ret);
	}
}

int main() {
	while (~scanf("%d%d", &N, &T)) {
		for (int i = 1; i < N; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c); addEdge(b, a, c);
		}
		for (int i = 1; i <= N; i++)
			scanf("%d", &cost[i]);
		spfa(1);
	}
	return 0;
}

