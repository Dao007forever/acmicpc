/*
 * Author: Yang Zhang
 * Created Time: Sat 08 Sep 2012 03:02:51 PM CST
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

#define maxn 10005
const int maxm = 4*maxn;
const LL inf = 1ll<<50;
int n, m, cnt;
int st[maxn], ed[maxn];
vector<int> adj[maxn];
struct Edge {
	int v, next;
	LL w;
};
struct Graph {
	int N, M;
	Edge edge[maxm * 2];
	int num, Head[maxn];
	LL dis[maxn];
	bool vis[maxn];
	int cnt[maxn];

	void init(int N) {
		this->N = N;
		num = 0;
		memset(cnt, 0, sizeof(cnt));
		memset(Head, -1, sizeof(Head));
	}

	void addEdge(int u, int v, LL w) {
		cout << u << " " << v << " " << w << endl;
		edge[num].v = v;
		edge[num].w = w;
		edge[num].next = Head[u];
		Head[u] = num++;
	}

	bool SPFA(int st) {
		for (int i = 0; i <= N; i++) {
			dis[i] = inf;
			vis[i] = false;
		}
		vis[st] = true;
		dis[st] = 0;
		cnt[st]++;
		queue<int> Q;
		Q.push(st);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			vis[u] = false;
			for (int i = Head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].v;
				if (dis[u] + edge[i].w < dis[v]) {
					dis[v] = dis[u] + edge[i].w;
					if (!vis[v]) {
						vis[v] = true;
						cnt[v]++;
						if (cnt[v] > N) return false;
						Q.push(v);
					}
				}
			}
		}
		return true;
	}
}g;

void dfs(int u, int fa) {
	st[u] = cnt;
	for (int i = 0, v; i < adj[u].size(); i++) {
		if ((v = adj[u][i]) != fa) {
			dfs(v, u);
		}
	}
	ed[u] = cnt++;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i <= n; i++)
			adj[i].clear();
		for (int i = 2; i <= n; i++) {
			int x;
			scanf("%d", &x);
			adj[i].PB(x); adj[x].PB(i);
		}
		cnt = 1;
		dfs(1, 0);
		g.init(n + 1);
		g.addEdge(n + 1, 0, 0);
		for (int i = 1; i <= n; i++) {
			g.addEdge(i, i - 1, -1);
			g.addEdge(n + 1, i, 0);
		}
		scanf("%d", &m);
		while (m--) {
			int a, b;
			char op[5];
			scanf("%d %s %d", &a, op, &b);
			if (*op == '<') {
				g.addEdge(ed[a], st[a] - 1, b - 1);
			} else if (*op == '>') {
				g.addEdge(st[a] - 1, ed[a], -b - 1);
			} else {
				g.addEdge(st[a] - 1, ed[a], -b);
				g.addEdge(ed[a], st[a] - 1, b);
			}
		}
		if (g.SPFA(n + 1)) puts("Lie");
		else puts("True");
	}
	return 0;
}

