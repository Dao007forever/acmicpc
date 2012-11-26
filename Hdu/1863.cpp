#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 100000000;
int N, M, Sum;
int adj[111][111], dis[111], vis[111];

bool Prim() {
	Sum = 0;
	for (int i = 1; i <= N; i++) {
		dis[i] = inf;
		vis[i] = false;
	}
	dis[1] = 0;
	for (int i = 1; i <= N; i++) {
		int Min = inf, k = -1;
		for (int j = 1; j <= N; j++)
			if (!vis[j] && dis[j] < Min) {
				Min = dis[j];
				k = j;
			}
		if (k == -1) return false;
		vis[k] = true;
		Sum += dis[k];
		for (int j = 1; j <= N; j++)
			if (!vis[j] && adj[k][j] < dis[j]) {
				dis[j] = adj[k][j];
			}
	}
	return true;
}

int main()
{
	freopen("in.txt", "r", stdin);
	while (scanf("%d%d", &M, &N) && M) {
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				adj[i][j] = inf;
		for (int i = 0; i < M; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			adj[u][v] = adj[v][u] = w;
		}
		if (Prim()) {
			cout << Sum << endl;
		} else {
			cout << "?" << endl;
		}
	}
	return 0;
}
