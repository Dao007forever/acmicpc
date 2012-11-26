/*
 * Author: Yang Zhang
 * Created Time: Sun 01 Jul 2012 01:24:54 PM UTC
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

const int MAXN = 1005;
int x[MAXN], y[MAXN], c[MAXN];
bool vst[MAXN], adj[MAXN][MAXN];
int n, cnt;

LL dist(int i, int j) {
	return (LL)(x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

void dfs(int u) {
	cnt += c[u];
	vst[u] = true;
	for (int i = 1; i <= n; i++)
		if (i != u && !vst[i] && adj[u][i]) {
			dfs(i);
		}
}

int main() {
	while (~scanf("%d", &n) && n) {
		memset(vst, 0, sizeof(vst));
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < n; i++)
			scanf("%d%d%d", &x[i], &y[i], &c[i]);

		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (dist(i, j) <= 900) adj[i][j] = adj[j][i] = true;
		int ret = 0, pos;
		for (int i = 0; i < n; i++)
			if (!vst[i]) {
				cnt = 0;
				dfs(i);
				if (cnt > ret) {
					ret = cnt;
					pos = i;
				}
			}
		cout << pos + 1 << " " << ret << endl;
	}
	return 0;
}

