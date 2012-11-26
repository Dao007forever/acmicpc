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

const int maxn = 512;
int N, M, S, T;
int d[maxn];
vector<pair<int, int> > adj[maxn];
vector<int> ans[maxn];

void bfs() {
	memset(d, -1, sizeof(d));
	queue<int> Q;
	Q.push(S);
	d[S] = 0;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if (u == T) break;
		for (int i = 0, v; i < adj[u].size(); i++)
			if (d[v = adj[u][i].first] == -1) {
				d[v] = d[u] + 1;
				Q.push(v);
			}
	}
}

void output() {
	for (int u = 1; u <= N; u++)
		for (int i = 0; i < adj[u].size(); i++)
			if (d[u] + 1 == d[adj[u][i].first]) {
				ans[d[u]].PB(adj[u][i].second);
			}
	printf("%d\n", d[T]);
	for (int i = 0; i < d[T]; i++) {
		printf("%d", ans[i].size());
		for (int j = 0; j < ans[i].size(); j++)
			printf(" %d", ans[i][j]);
		printf("\n");
	}
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d%d%d%d", &N, &M, &S, &T);
	for (int i = 1; i <= M; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].PB(MP(b, i));
		adj[b].PB(MP(a, i));
	}
	bfs();
	output();
}
