/*
 * Author: Yang Zhang
 * Created Time: Wed 15 Aug 2012 08:07:00 PM UTC
 * File Name: 3169.cpp
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
int n, x, y;
int dis[MAXN], cnt[MAXN];
bool vis[MAXN];
vector<pair<int, int> > adj[MAXN];
void addEdge(int u, int v, LL w) {
	adj[u].PB(MP(v, w));
}

bool spfa(int st) {
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i <= n; i++) {
		dis[i] = inf;
		vis[i] = false;
	}
	dis[st] = 0; vis[st] = true;
	queue<int> q;
	q.push(st);
	cnt[st]++;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = false;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			LL w = adj[u][i].second;
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
					cnt[v]++;
					if (cnt[v] > n) return false;
				}
			}
		}
	}
	return true;
}
int main() {
	scanf("%d%d%d", &n, &x, &y);
	for (int i = 0; i < x; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w); //P[v]-P[u]<=w
	}
	for (int i = 0; i < y; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addEdge(v, u, -w); //P[v]-P[u]>=w
	}
	for (int i = 1; i < n; i++) {
		addEdge(i + 1, i, 0); //P[i+1]>=P[i]
	}
	if (!spfa(1)) puts("-1");
	else if (dis[n] == inf) puts("-2");
	else printf("%d\n", dis[n]);
	return 0;
}

