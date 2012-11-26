/*
 * Author: Yang Zhang
 * Created Time: Wed 29 Aug 2012 09:49:20 PM CST
 * File Name: 515.cpp
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

#define MAXN 100005
const int inf = 1000000000;
struct Edge {
	int v, w, next, id;
}e[MAXN << 1];
int Head[MAXN];
int n, m, K, E;
int p[MAXN], dis[MAXN], dp[MAXN], pre[MAXN];
bool vis[MAXN], inG[MAXN];
vector<int> ans;

void addEdge(int u, int v, int w, int idx) {
	e[E].v = v; e[E].w = w; e[E].id = idx; e[E].next = Head[u]; Head[u] = E++;
}

priority_queue<pair<int, int> > q;
void dijkstra(int st) {
	for (int i = 0; i <= n; i++)
		dis[i] = inf, vis[i] = false;
	dis[st] = 0;
	q.push(MP(0, st));
	while (!q.empty()) {
		int u = q.top().second; q.pop();
		vis[u] = true;
		for (int i = Head[u]; i != -1; i = e[i].next) {
			int v = e[i].v, w = e[i].w;
			if (!vis[v] && dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				q.push(MP(-dis[v], v));
			}
		}
	}
}

bool cmp(int a, int b) {
	return dis[a] < dis[b];
}

int dfs(int u) {
	if (dp[u] != -1) return dp[u];
	dp[u] = 0;
	for (int i = Head[u]; i != -1; i = e[i].next) {
		int v = e[i].v, w = e[i].w;
		if (dis[v] + w == dis[u]) {
			int cnt = dfs(v);
			if (cnt > dp[u]) {
				dp[u] = cnt;
				pre[u] = i;
			}
		}
	}
	if (inG[u]) dp[u]++;
	return dp[u];
}

void output(int x) {
	if (x != -1) {
		output(pre[e[x].v]);
	}
	if (e[x].id) ans.PB(e[x].id);
}

int main() {
	E = 0;
	memset(Head, -1, sizeof(Head));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c, i + 1); addEdge(b, a, c, i + 1);
	}
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d", &p[i]);
		inG[p[i]] = true;
	}
	dijkstra(p[0]);
	int start = p[0];
	for (int i = 0; i < K; i++) {
		if (dis[p[i]] > dis[start]) {
			start = p[i];
		}
	}
	dijkstra(start);
	int end = start;
	for (int i = 0; i < K; i++) {
		if (dis[p[i]] > dis[end]) {
			end = p[i];
		}
	}

	memset(dp, -1, sizeof(dp));
	dp[start] = 1;
	pre[start] = -1;
	dfs(end);
	output(pre[end]);
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++)
		printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	return 0;
}

