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

#define MAXN 305
const int inf = 100000000;
struct Vertex {
	int u, d;
};
int n, m;
int A, B, C, D;
int da[MAXN], dc[MAXN], adj[MAXN][MAXN], dp[MAXN][MAXN];
bool vst[MAXN];

void dijkstra(int st, int d[]) {
	for (int i = 1; i <= n; i++)
		d[i] = inf;
	d[st] = 0;
	priority_queue<pair<int, int> > Q;
	Q.push(MP(0, st));
	while (!Q.empty()) {
		pair<int, int> cur = Q.top(); Q.pop();
		int u = cur.second;
		for (int i = 1; i <= n; i++)
			if (adj[u][i] < inf && d[u] + adj[u][i] < d[i]) {
				d[i] = d[u] + adj[u][i];
				Q.push(MP(-d[i], i));
			}
	}
}

int dfs(int u, int v) {
	if (dp[u][v] != -1) return dp[u][v];
	int ret = 0;
	if (u == v) ret++;
	if (u == v) {
		for (int i = 1; i <= n; i++)
			if (da[i] + adj[i][u] == da[u]) {
				for (int j = 1; j <= n; j++)
					if (dc[j] + adj[j][v] == dc[v]) {
						ret = max(ret, dfs(i, j) + 1);
					}
			}
	}
	for (int i = 1; i <= n; i++)
		if (da[i] + adj[i][u] == da[u]) {
			ret = max(ret, dfs(i, v));
		}
	for (int j = 1; j <= n; j++)
		if (dc[j] + adj[j][v] == dc[v]) {
			ret = max(ret, dfs(u, j));
		}
	return dp[u][v] = ret;
}

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &m) && n + m) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				adj[i][j] = inf;
		while (m--) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			adj[a][b] = adj[b][a] = min(adj[a][b], c);
		}
		scanf("%d%d%d%d", &A, &B, &C, &D);
		dijkstra(A, da);
		dijkstra(C, dc);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dp[i][j] = -1;
		dp[A][C] = 0;
		int ret = dfs(B, D);
		printf("%d\n", ret);
	}
	return 0;
}
