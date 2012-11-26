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

#define MAXN 205
#define MAXM 1005
const int inf = 1000000000;
int n, m;
int f[MAXN];
int dist[MAXN][MAXN];
queue<int> Q;

void Floyd() {
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

void output() {
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 1; i <= n; i++)
			if (dist[u][i] == 1 && !f[i]) {
				cout << u << " " << i << endl;
				Q.push(i);
				f[i] = 1;
			}
	}
}

int main() {
	freopen("in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j) dist[i][j] = n + 1;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		dist[u][v] = dist[v][u] = 1;
	}
	
	Floyd();
	int ans, center, Min = n;
	for (int i = 1; i <= n; i++) {
		int s = 0;
		for (int j = 1; j <= n; j++)
			s = max(s, dist[i][j]);
		int j;
		bool flag = false;
		for (j = 1; j <= n; j++)
			if (dist[i][j] == 1) {
				flag = true;
				for (int k = 1; k <= n; k++)
					if (dist[i][k] == s) {
						if (dist[j][k] != s - 1) {
							flag = false;
							break;
						}
					}
				if (flag) break;
			}
		if (flag) s = 2 * s - 1;
		else s = 2 * s;
		if (s < Min) {
			Min = s;
			ans = i;
			if (flag) center = j;
		}
	}

	if (Min % 2 == 0) {
		Q.push(ans);
		f[ans] = 1;
	} else {
		Q.push(ans);
		Q.push(center);
		cout << ans << " " << center << endl;
		f[ans] = f[center] = 1;
	}
	output();
	return 0;
}
