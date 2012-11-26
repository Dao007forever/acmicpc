/*
 * Author: Yang Zhang
 * Created Time: Wed 12 Sep 2012 08:11:47 PM CST
 * File Name: 3509.cpp
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

#define MAXN 505
#define MAXM 50005
struct Operation {
	char op;
	int u, v;
	Operation() {}
	Operation(char op, int u, int v) : op(op), u(u), v(v) {}
};

int minid, x, y;
vector<int> adj[MAXN];
int t[MAXN][MAXN];

bool dfs(int s, int e, int p) {
	if (s == e) return true;
	for (vector<int>::iterator it = adj[s].begin(); it != adj[s].end(); it++) {
		if (*it != p && dfs(*it, e, s)) {
			if (t[s][*it] < minid) {
				minid = t[s][*it];
				x = s; y = *it;
			}
			return true;
		}
	}
	return false;
}

int main() {
	int n, m;
	int cas = 0;
	while (~scanf("%d%d\n", &n, &m)) {
		if (cas) puts("");
		printf("Case %d:\n", ++cas);
		vector<Operation> p;
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			for (int j = 0; j < n; j++)
				t[i][j] = MAXM;
		}
		for (int i = 0; i < m; i++) {
			int u, v;
			char op;
			scanf("%c %d %d\n", &op, &u, &v);
			u--; v--;
			p.PB(Operation(op, u, v));
			if (op == 'D') t[u][v] = t[v][u] = i;
		}
		for (int i = 0; i < m; i++) {
			int u = p[i].u, v = p[i].v;
			if (p[i].op == 'I') {
				minid = MAXM;
				if (dfs(u, v, -1)) {
					if (minid < t[u][v]) {
						adj[x].erase(remove(adj[x].begin(), adj[x].end(), y), adj[x].end());
						adj[y].erase(remove(adj[y].begin(), adj[y].end(), x), adj[y].end());
						adj[u].PB(v);
						adj[v].PB(u);
					}
				} else {
					adj[u].PB(v);
					adj[v].PB(u);
				}
			} else if (p[i].op == 'D') {
				adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
				adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
			} else {
				if (dfs(u, v, -1)) puts("YES");
				else puts("NO");
			}
		}
	}
	return 0;
}

