/*
 * Author: Yang Zhang
 * Created Time: Fri 14 Sep 2012 09:43:37 PM CST
 * File Name: 3760.cpp
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
#define MAXM 200005
int n, m;
struct node {
	int v, c;
	node() {}
	node(int v, int c) : v(v), c(c) {}
	bool operator < (const node &p) const {
		return c < p.c;
	}
};
vector<node> adj[MAXN];
int dis[MAXN], pre[MAXN], path[MAXN];

void addEdge(int u, int v, int w) {
	adj[u].PB(node(v, w));
}

void bfs(int st) {
	for (int i = 0; i < n; i++) dis[i] = MAXN, pre[i] = -1;
	dis[st] = 0;
	queue<int> q;
	q.push(st);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].v, c = adj[u][i].c;
			if (dis[u] + 1 < dis[v]) {
				dis[v] = dis[u] + 1;
				pre[v] = u;
				path[v] = c;
				q.push(v);
			} else if (dis[v] == dis[u] + 1) {
				if (c < path[v]) {
					path[v] = c;
					pre[v] = u;
				}	
			}
		}
	}
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) adj[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			addEdge(a, b, c);
			addEdge(b, a, c);
		}
		for (int i = 0; i < n; i++)
			sort(adj[i].begin(), adj[i].end());
		bfs(n - 1);
		vector<int> ans;
		for (int i = 0; pre[i] != -1; i = pre[i]) {
			ans.PB(path[i]);
		}
		printf("%d\n", ans.size());
		for (int i = 0; i < ans.size(); i++)
			printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	}
	return 0;
}

