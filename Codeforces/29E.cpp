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

#define MAXN 505
const int inf = 100000000;
struct node {
	int a, b, c;
};
int n, m;
int dist[MAXN][MAXN][2], pre[MAXN][MAXN][2];
vector<int> adj[MAXN], ansa, ansb;

void bfs() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dist[i][j][0] = dist[i][j][1] = inf;
	dist[1][n][0] = 0;
	node s;
	s.a = 1; s.b = n; s.c = 0;
	queue<node> Q;
	Q.push(s);
	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		if (s.a == n && s.b == 1) return;
		if (s.c == 0) {
			for (int i = 0; i < adj[s.a].size(); i++) {
				int v = adj[s.a][i];
				if (dist[s.a][s.b][0] + 1 < dist[v][s.b][1]) {
					dist[v][s.b][1] = dist[s.a][s.b][0] + 1;
					pre[v][s.b][1] = s.a;
					node t;
					t.a = v; t.b = s.b; t.c = 1;
					Q.push(t);
				}
			}
		} else {
			for (int i = 0; i < adj[s.b].size(); i++) {
				int v = adj[s.b][i];
				if (v == s.a) continue;
				if (dist[s.a][s.b][1] + 1 < dist[s.a][v][0]) {
					dist[s.a][v][0] = dist[s.a][s.b][1] + 1;
					pre[s.a][v][0] = s.b;
					node t;
					t.a = s.a; t.b = v; t.c = 0;
					Q.push(t);
				}
			}
		}
	}
}

int main() {
	freopen("in", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].PB(b); adj[b].PB(a);
	}
	bfs();
	if (dist[n][1][0] == inf) {
		cout << -1 << endl;
		return 0;
	}
	cout << dist[n][1][0] / 2 << endl;
	ansa.PB(n);
	ansb.PB(1);
	int k1 = n, k2 = 1;
	for (int i = 0; i < dist[n][1][0] / 2; i++) {
		k2 = pre[k1][k2][0];
		ansb.PB(k2);
		k1 = pre[k1][k2][1];
		ansa.PB(k1);
	}
	reverse(ansa.begin(), ansa.end());
	reverse(ansb.begin(), ansb.end());
	for (int i = 0; i < ansa.size(); i++)
		printf("%d%c", ansa[i], i == ansa.size() - 1 ? '\n' : ' ');
	for (int i = 0; i < ansb.size(); i++)
		printf("%d%c", ansb[i], i == ansb.size() - 1 ? '\n' : ' ');
	return 0;
}
