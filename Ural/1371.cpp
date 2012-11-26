/*
 * 一棵树，t(i,j)表示树中ij两个结点的距离，求树中任意两点的平均距离，即sum(t(i,j))/N*(N-1)
 * 树形dp，每个子树记录两个值，这个子树所有点之间的距离之和，这个子树所有点到子树根的距离和，原来crash(stack overflow)了，看了yhch的代码，加了第一句就ac了
 */
#pragma comment(linker, "/STACK:16777216")
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 50005
struct Edge {
	int v, next, w;
}edge[2 * MAXN];
int N;
long long Num[MAXN], dist[MAXN], f[MAXN];
int num, Head[MAXN];
vector<int> adj[MAXN], cost[MAXN];

void dfs(int u, int fa)
{
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa)
			dfs(adj[u][i], u);
	Num[u] = 1;
	dist[u] = 0;
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			Num[u] += Num[v];
			dist[u] += dist[v] + Num[v] * cost[u][i];
		}
	f[u] = 0;
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			f[u] += (dist[v] + Num[v] * cost[u][i]) * (Num[u] - Num[v]);
		}
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa)
			f[u] += f[adj[u][i]];
}

int main()
{
	freopen("in.txt", "r", stdin);
	num = 0;
	memset(Head, -1, sizeof(Head));
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(v); cost[u].push_back(w);
		adj[v].push_back(u); cost[v].push_back(w);
	}
	dfs(1, 0);
	double ret = (double)f[1] * 2.0 / ((double)N * (N - 1));
	printf("%.4f\n", ret);
	return 0;
}
