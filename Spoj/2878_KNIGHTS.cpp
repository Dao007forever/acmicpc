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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 1005
struct Graph {
	bool adj[MAXN][MAXN];
	int dfn[MAXN], low[MAXN];
	bool vst[MAXN];
	int N, M, size, depth;
	stack<int> S;
	int block[MAXN], numB;
	int col[MAXN];
	bool odd;
	int que[MAXN];

	void init(int n) {
		N = n;
		//memset(adj, 0, sizeof(adj));
	}

	void dfs(int u, int c) {
		if (odd) return;
		if (col[u] != -1) {
			if (col[u] != c) {
				odd = true;
			}
			return;
		}
		col[u] = c;
		for (int i = 0; i < numB; i++)
			if (adj[u][block[i]]) {
				dfs(block[i], 1 - c);
			}
	}

	void CheckBlock() {
		if (numB == 1) return;
		for (int i = 0; i < numB; i++) {
			col[block[i]] = -1;
			//printf("%d ", block[i]);
		}
		//printf("\n");
		odd = false;
		dfs(block[0], 0);
		if (odd) {
			for (int i = 0; i < numB; i++)
				vst[block[i]] = true;
		}
	}

	void Tarjan(int u) {
	    dfn[u] = low[u] = depth++;
		S.push(u);
		for (int v = 0; v < N; v++) {
			if (adj[u][v]) {
				adj[v][u] = 0;
				if (dfn[v] == -1) {
					Tarjan(v);
					low[u] = min(low[u], low[v]);
					if (low[v] >= dfn[u]) {
						numB = 0;
						int x;
						do {
							x = S.top(); S.pop();
							block[numB++] = x;
						} while (x != v);
						block[numB++] = u;
						CheckBlock();
					}
				} else {
					low[u] = min(low[u], dfn[v]);
				}
			}
		}
	}

	void BCC() {
		depth = 0; size = 0;
		while (!S.empty()) S.pop();
		for (int i = 0; i < N; i++)
			dfn[i] = -1, vst[i] = false;
	    for (int i = 0; i < N; i++)
		    if (dfn[i] == -1) Tarjan(i);
		int ret = 0;
		for (int i = 0; i < N; i++)
			ret += vst[i];
		printf("%d\n", N - ret);
	}

}g;

/*
 Poj2942
 求点双连通分量+判奇圈
 邻接矩阵实现
 */
int main() {
	freopen("in.txt", "r", stdin);
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		g.init(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g.adj[i][j] = i != j;
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			g.adj[a][b] = g.adj[b][a] = 0;
		}
		g.BCC();
	}
	return 0;
}