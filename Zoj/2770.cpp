/*
 * Author: Yang Zhang
 * Created Time: Wed 15 Aug 2012 06:57:22 PM UTC
 * File Name: 2770.cpp
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
const LL inf = 1LL<<40;
int n, m;
vector<pair<int, LL> > adj[MAXN];
LL dis[MAXN], sum[MAXN];
int c[MAXN], cnt[MAXN];
bool vis[MAXN];

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
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i <= n; i++)
			adj[i].clear();
		sum[0] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &c[i]);
			sum[i] = sum[i - 1] + c[i];
		}
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(v, u - 1, -w); //S[v] - S[u - 1] >= w
			addEdge(u - 1, v, sum[v] - sum[u - 1]); //S[v] - S[u - 1] <= sigma{C[u]+...C[v]} = sum[v] - sum[u - 1]
		}
		for (int i = 1; i <= n; i++) {
			addEdge(i, i - 1, 0); //S[i]-S[i - 1] >= 0
			addEdge(i - 1, i, c[i]); //S[i]-S[i - 1] <= C[i]
		}
		if (!spfa(n)) puts("Bad Estimations");
		else cout << -dis[0] << endl;
	}
	return 0;
}
