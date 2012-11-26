/*
 * Author: Yang Zhang
 * Created Time: Wed 22 Aug 2012 10:04:43 PM CST
 * File Name: 3416.cpp
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
typedef int F;
#define inf (1 << 29)
#define maxV 1010
#define maxE 400000
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	void addCap(int x, int y, int f) {
		cap[E] = f; flow[E] = 0; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
		cap[E] = 0; flow[E] = 0; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
	}

	bool bfs(int s, int t) {
		for (int i = 0; i < V; i++)
			level[i] = -1;
		queue<int> q;
		q.push(s); level[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (int i = last[x]; i != -1; i = prev[i])
				if (level[to[i]] == -1 && cap[i] > flow[i]) {
					q.push(to[i]);
					level[to[i]] = level[x] + 1;
				}
		}
		return (level[t] != -1);
	}

	F dfs(int v, int t, F f) {
		if (v == t) return f;
		for (int i = used[v]; i != -1; used[v] = i = prev[i])
			if (level[to[i]] > level[v] && cap[i] > flow[i]) {
				F tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
				if (tmp > 0) {
					flow[i] += tmp;
					flow[i ^ 1] -= tmp;
					return tmp;
				}
			}
		return 0;
	}

	F solve(int s, int t) {
		while (bfs(s, t)) {
			for (int i = 0; i < V; i++) used[i] = last[i];
			while (dfs(s, t, inf) != 0);
		}
		F ans = 0;
		for (int i = last[s]; i != -1; i = prev[i])
			ans += flow[i];
		return ans;
	}
}mf;
int n, m, st, ed;
int num;
int to[maxE], prev[maxE], cost[maxE];
int dis[maxV], last[maxV], vis[maxV];

void addEdge(int u, int v, int w) {
	to[num] = v; cost[num] = w; prev[num] = last[u]; last[u] = num++;
}

priority_queue<pair<int, int> > q;
void dijkstra() {
	for (int i = 1; i <= n; i++)
		dis[i] = inf, vis[i] = false;
	dis[st] = 0;
	q.push(MP(0, st));
	while (!q.empty()) {
		int u = q.top().second; q.pop();
		vis[u] = true;
		for (int i = last[u], v; i != -1; i = prev[i]) {
			if (!vis[v = to[i]] && dis[u] + cost[i] < dis[v]) {
				dis[v] = dis[u] + cost[i];
				q.push(MP(-dis[v], v));
			}
		}
	}
}

void solve() {
	mf.init(n + 2);
	int source = 0, sink = n + 1;
	mf.addCap(source, st, inf);
	mf.addCap(ed, sink, inf);
	for (int u = 1; u <= n; u++) {
		for (int i = last[u]; i != -1; i = prev[i])
			if (dis[u] + cost[i] == dis[to[i]]) {
				mf.addCap(u, to[i], 1);
			}
	}
	int ret = mf.solve(source, sink);
	printf("%d\n", ret);
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		num = 0;
		memset(last, -1, sizeof(last));
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
		}
		scanf("%d%d", &st, &ed);
		dijkstra();
		solve();
	}
	return 0;
}

