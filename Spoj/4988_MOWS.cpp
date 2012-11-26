/*
 * Author: Yang Zhang
 * Created Time: Tue 28 Aug 2012 09:18:19 PM CST
 * File Name: 4988_MOWS.cpp
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
#define MAXN 110000
struct Graph {
	int n, size, depth;
	vector<int> adj[MAXN];
	int low[MAXN], dfn[MAXN], id[MAXN];
	bool vis[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
		memset(id, 0, sizeof(id));
		memset(vis, 0, sizeof(vis));
		while (!S.empty()) S.pop();
	}

	void addEdge(int u, int v) {
		adj[u].PB(v);
	}

	void Tarjan(int u) {
		dfn[u] = low[u] = depth++;
		S.push(u);
		vis[u] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dfn[v] == -1) {
				Tarjan(v);
				low[u] = min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			size++;
			int v;
			do {
				v = S.top();
				S.pop();
				id[v] = size;
				vis[v] = false;
			} while (u != v);
		}
	}

	void SCC() {
		memset(dfn, -1, sizeof(dfn));
		size = 0;
		depth = 1;
		for (int i = 0; i < n; i++)
			if (dfn[i] == -1) Tarjan(i);
	}

}g;

int n, m, s;
int cnt[MAXN];

int change(int x) {
	if (x <= 1000) return x - 1;
	return n + x - 1001;
}
int main() {
	int Test;
	scanf("%d", &Test);
	for (; Test--; ) {
		scanf("%d%d%d", &n, &m, &s);
		g.init(n + m);
		for (int i = 0; i < s; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a = change(a); b = change(b);
			g.addEdge(a, b);
			//cout << a << " " << b << endl;
		}
		g.SCC();
		memset(cnt, 0, sizeof(cnt));
		for (int i = n; i < n + m; i++)
			cnt[g.id[i]]++;
		int ret = 0, Max = 0;
		for (int i = 0; i < n; i++)
			if (cnt[g.id[i]] > Max) {
				Max = cnt[g.id[i]];
				ret = i;
			}
		printf("%d %d\n", ret + 1, Max);
	}
	return 0;
}

