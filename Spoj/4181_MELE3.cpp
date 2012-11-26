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
const int inf = 100000000;
int n, m;
vector<int> adj[MAXN];
bool vis[MAXN];
int dis[MAXN];

void spfa(int st) {
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
			int v = adj[u][i];
			int k, w, d;
			if (u < v) {
				k = dis[u] % (2 * (v - u));
				if (k == 0) w = 0;
				else w = 2 * (v - u) - k;
				d = v - u;
			} else {
				k = dis[u] % (2 * (u - v));
				if (k == 0) {
					w = 0;
				} else if (k <= (u - v)) {
					w = u - v - k;
				} else {
					w = 2 * (u - v) - k + u - v;
				}
				d = u - v;
			}
			if (dis[u] + w + d < dis[v]) {
				dis[v] = dis[u] + w + d;
				if (!vis[v]) {
					vis[v] = true;
					Q.push(v);
				}
			}

		}
	}
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].PB(b); adj[b].PB(a);
	}
	spfa(1);
	printf("%d\n", dis[n] * 5);
}
