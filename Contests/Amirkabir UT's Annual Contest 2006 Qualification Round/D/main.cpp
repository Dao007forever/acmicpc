/*
 * Author: Yang Zhang
 * Created Time: Fri 29 Jun 2012 09:06:36 PM UTC
 * File Name: main.cpp
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

#define MAXM 1005
#define MAXN 605
const int inf = 1LL << 30;
const double eps = 1e-6;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
int n, m, st;
int f[MAXM][MAXN];
vector<pair<int, int> > adj[MAXN];

void addEdge(int u, int v, int w) {
	adj[u].PB(MP(v, w));
}

void solve() {
	for (int i = 0; i <= 1000; i++)
		for (int j = 0; j < n; j++)
			f[i][j] = inf;
	f[0][st] = 0;

	for (int i = 0; i < 1000; i++)
		for (int j = 0; j < n; j++)
			if (f[i][j] < inf) {
				for (int k = 0; k < adj[j].size(); k++)
					f[i + 1][adj[j][k].first] = min(f[i + 1][adj[j][k].first], f[i][j] + adj[j][k].second);
			}
}

int main() {
	while (~scanf("%d%d%d", &n, &m, &st)) {
		for (int i = 0; i < n; i++)
			adj[i].clear();
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w);
		}
		solve();
		int q;
		scanf("%d", &q);
		while (q--) {
			int t;
			scanf("%d", &t);
			if (st == t) {
				printf("0.0000 0\n");
				continue;
			}
			double ret = 1e50; int ans = -1;
			for (int i = 1; i <= 1000; i++) {
				if (f[i][t] == inf) continue;
				double tmp = (double)f[i][t] / i;
				if (sig(tmp - ret) < 0) {
					ret = tmp;
					ans = i;
				}
			}
			if (ans < 0) {
				cout << "No Path" << endl;
				continue;
			}
			printf("%.4f %d\n", ret, ans);
		}
		cout << endl;
	}
	return 0;
}

