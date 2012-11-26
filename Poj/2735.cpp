/*
 * Author: Yang Zhang
 * Created Time: Mon 10 Sep 2012 08:41:21 PM CST
 * File Name: 2735.cpp
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

const int inf = 1000000000;
struct Edge {
	int a, b, c;
}e[22];
struct Graph {
	int n, bridge;
	vector<pair<int, int> > graph[16];
	int dfn[16], low[16];
	bool visit[22];
	
	void init(int n) {
		this->n = n;
		memset(visit, 0, sizeof(visit));
		for (int i = 1; i <= n; i++)
			graph[i].clear();
		bridge = 0;
	}

	void addEdge(int u, int v, int id) {
		graph[u].PB(MP(v, id));
		graph[v].PB(MP(u, id));
	}

	void Tarjan(int u, int dep) {
		dfn[u] = low[u] = dep;
	    for (int i = 0; i < graph[u].size(); i++) {
		    int v = graph[u][i].first;
			int id = graph[u][i].second;
	        if (dfn[v] == -1) {
		        visit[id] = true;
			    Tarjan(v, dep + 1);
				low[u] = min(low[u], low[v]);
				if (low[v] > dfn[u]) bridge++;
		    } else if (!visit[id]) {
			    low[u] = min(low[u], dfn[v]);
			}
		}
	}

	bool Bridge() {
		int cnt = 0;
		for (int i = 1; i <= n; i++)
			dfn[i] = -1;
		for (int i = 1; i <= n; i++)
			if (dfn[i] == -1) {
				Tarjan(i, 0);
				cnt++;
			}
		if (cnt == 1 && bridge == 0) return true;
		return false;
	}
}g;
struct DisJointSet{
	int rank[22], parent[22];

	void init(int n) {
		for (int i = 0; i <= n; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}
}dsu;
int n, m;

int main() {
	int cas = 1;
	while (scanf("%d%d", &n, &m) && n + m) {
		for (int i = 0; i < m; i++)
			scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].c);
		int ret = inf, sum;
		for (int s = 0; s < (1 << m); s++) {
			int cnt = 0;
			dsu.init(n);
			for (int i = 0; i < m; i++)
				if (s & (1 << i)) {
					dsu.Union(e[i].a, e[i].b);
					cnt++;
				}
			if (cnt < n) continue;
			bool flag = true;
			for (int i = 2; i <= n; i++)
				if (dsu.Find(1) != dsu.Find(i)) {
					flag = false;
					break;
				}
			if (!flag) continue;
			g.init(n);
			sum = 0;
			for (int i = 0; i < m; i++)
				if (s & (1 << i)) {
					g.addEdge(e[i].a, e[i].b, i);
					sum += e[i].c;
				}
			flag = g.Bridge();
			if (flag) {
				ret = min(ret, sum);
			}
		}
		if (ret == inf) {
			printf("There is no reliable net possible for test case %d.\n", cas++);
		} else {
			printf("The minimal cost for test case %d is %d.\n", cas++, ret);
		}
	}
	return 0;
}
