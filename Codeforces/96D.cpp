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
const LL inf = 1LL << 60;
int n, m, x, y;
int t[MAXN], c[MAXN];
int vis[MAXN];
LL dis[MAXN], minc[MAXN];
vector<pair<int, int> > adj[MAXN], cost[MAXN];

void SPFA1(int st) {
	for (int i = 1; i <= n; i++) {
		dis[i] = inf;
		vis[i] = false;
	}
	vis[st] = true;
	dis[st] = 0;
	queue<int> Q;
	Q.push(st);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		vis[u] = false;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			if (dis[u] + (LL)adj[u][i].second < dis[v]) {
				dis[v] = dis[u] + (LL)adj[u][i].second;
				if (!vis[v]) {
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}

	for (int i = 1; i <= n; i++)
		if (i != st && dis[i] <= t[st]) {
			cost[st].PB(MP(i, c[st]));
		}
}

void SPFA2(int st) {
	for (int i = 1; i <= n; i++) {
		minc[i] = inf;
		vis[i] = false;
	}
	vis[st] = true;
	minc[st] = 0;
	queue<int> Q;
	Q.push(st);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		vis[u] = false;
		for (int i = 0; i < cost[u].size(); i++) {
			int v = cost[u][i].first;
			if (minc[u] + (LL)cost[u][i].second < minc[v]) {
				minc[v] = minc[u] + (LL)cost[u][i].second;
				if (!vis[v]) {
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}
}

int main() {
//	freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	scanf("%d%d", &x, &y);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		adj[a].PB(MP(b, c));
		adj[b].PB(MP(a, c));
	}
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &t[i], &c[i]);

	for (int i = 1; i <= n; i++)
		SPFA1(i);
	SPFA2(x);
	if (minc[y] == inf) minc[y] = -1LL;
	cout << minc[y] << endl;
	return 0;
}
