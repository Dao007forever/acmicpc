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

const int MAXN = 1000 + 10;
int n, m;
int sx, sy, cnt, ret;
int Map[MAXN][MAXN], L[MAXN][MAXN], R[MAXN][MAXN], U[MAXN][MAXN], D[MAXN][MAXN];

void dfs(int x, int y, int now, int dir) {
	if (x == sx && y == sy) {
		cnt++;
		if (cnt == 2) {
			cnt--;
			if (now > ret) ret = now;
			return;
		}
	}
	if (L[x][y] != y && dir - 1 != 0) dfs(x, L[x][y], now + y - L[x][y], -1);
	if (R[x][y] != y && dir + 1 != 0) dfs(x, R[x][y], now + R[x][y] - y, 1);
	if (D[x][y] != x && dir - 2 != 0) dfs(D[x][y], y, now + x - D[x][y], -2);
	if (U[x][y] != x && dir + 2 != 0) dfs(U[x][y], y, now + U[x][y] - x, 2);
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		char str[MAXN];
		scanf("%s", str + 1);
		for (int j = 1; j <= m; j++) {
			if (str[j] == '1') Map[i][j] = 1;
			else Map[i][j] = 0;
		}
	}

	for (int i = 1; i <= n; i++) {
		Map[i][0] = Map[i][m + 1] = -1;
		for (int j = 1; j <= m; j++)
			L[i][j] = R[i][j] = j;
		for (int j = 1; j <= m; j++) {
			while (Map[i][L[i][j] - 1] == 1)
				L[i][j] = L[i][L[i][j] - 1];
		}
		for (int j = m; j >= 1; j--) {
			while (Map[i][R[i][j] + 1] == 1)
				R[i][j] = R[i][R[i][j] + 1];
		}
	}
	for (int j = 1; j <= m; j++) {
		Map[0][j] = Map[n + 1][j] = -1;
		for (int i = 1; i <= n; i++)
			D[i][j] = U[i][j] = i;
		for (int i = 1; i <= n; i++) {
			while (Map[D[i][j] - 1][j] == 1)
				D[i][j] = D[D[i][j] - 1][j];
		}
		for (int i = n; i >= 1; i--) {
			while (Map[U[i][j] + 1][j] == 1)
				U[i][j] = U[U[i][j] + 1][j];
		}
	}

	ret = 0;
	for (int i = 1; i <= n; i++) 
	for (int j = 1; j <= m; j++)
	if (Map[i][j] == 1) {
		if (L[i][j] != j && R[i][j] != j) continue;
		if (D[i][j] != i && U[i][j] != i) continue;
		sx = i, sy = j;
		cnt = 0;
		dfs(i, j, 0, 0);
	}
	printf("%d\n", ret);
	return 0;
}
