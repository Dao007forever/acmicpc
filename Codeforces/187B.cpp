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

int f[66][66][66];
int d[66][66][66];
int n, m, r;

int main() {
//	freopen("in", "r", stdin);
	scanf("%d%d%d", &n, &m, &r);
	memset(f, 63, sizeof(f));
	for (int u = 1; u <= m; u++) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &d[u][i][j]);

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					d[u][i][j] = min(d[u][i][j], d[u][i][k] + d[u][k][j]);

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				f[0][i][j] = min(f[0][i][j], d[u][i][j]);
	}

	for (int l = 1; l <= n; l++) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				f[l][i][j] = f[l - 1][i][j];

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					f[l][i][j] = min(f[l][i][j], f[l - 1][i][k] + f[0][k][j]);
	}
	for (int i = 0; i < r; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		w = min(w, n);
		printf("%d\n", f[w][u][v]);
	}
	return 0;
}
