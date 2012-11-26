#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int N, tot;
int vis[1111], x[1111], y[1111];
vector<int> adj[1111];

void dfs(int u, int dep) {
	vis[u] = true;
	tot += 2;
	x[u] = dep, y[u] = tot;
	for (int i = 0; i < adj[u].size(); i++)
		if (!vis[adj[u][i]])
			dfs(adj[u][i], dep + 2);
}

int main() {
	freopen("in.txt", "r", stdin);
	cin >> N;
	for (int i = 1; i < N; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, tot = -1000);
	for (int i = 1; i <= N; i++)
		printf("%d %d\n", x[i], y[i]);
	return 0;
}
