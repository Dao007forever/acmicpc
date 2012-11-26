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

const int inf = 1000000;
int n, m;
char str[1111];
vector<int> adj[2222];
int dist[2222];

void bfs(int start) {
	for (int i = 1; i <= n + m; i++)
		dist[i] = inf;
	dist[start] = 0;
	queue<int> Q;
	Q.push(start);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dist[u] + 1 < dist[v]) {
				dist[v] = dist[u] + 1;
				Q.push(v);
			}
		}
	}
}

int main() {
	freopen("in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%s", str + 1);
		for (int j = 1; j <= m; j++)
			if (str[j] == '#') {
				adj[i].push_back(n + j);
				adj[n + j].push_back(i);
			}
	}
	bfs(n);
	if (dist[1] >= inf)
		dist[1] = -1;
	cout << dist[1] << endl;
	return 0;
}
