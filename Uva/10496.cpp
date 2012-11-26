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

#define abs(x) ((x) > 0 ? (x) : -(x))
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};
int dp[11][1 << 11];
int dist[11][11];
int x[11], y[11];
int n, m, num;
int sx, sy;

int distance(int X1, int Y1, int X2, int Y2) {
	return abs(X1 - X2) + abs(Y1 - Y2);
}

int DP(int mask, int k) {
	if (dp[k][mask] >= 0) return dp[k][mask];
	dp[k][mask] = 1 << 30;
	for (int i = 0; i < num; i++)
		if (mask & (1 << i)) {
			int tmp = DP(mask ^ (1 << k), i);
			if (tmp + dist[i][k] < dp[k][mask])
				dp[k][mask] = tmp + dist[i][k];
		}
	return dp[k][mask];
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> n >> m;
		cin >> sx >> sy;
		cin >> num;
		for (int i = 0; i < num; i++)
			cin >> x[i] >> y[i];
		for (int i = 0; i < num; i++)
			for (int j = 0; j < num; j++)
				dist[i][j] = distance(x[i], y[i], x[j], y[j]);
		memset(dp, -1, sizeof(dp));
		for (int i = 0; i < num; i++)
			dp[i][1 << i] = distance(sx, sy, x[i], y[i]);
		int ret = 1 << 30;
		for (int i = 0; i < num; i++) {
			int tmp = DP((1 << num) - 1, i);
			int t = distance(x[i], y[i], sx, sy);
			if (tmp + t < ret)
				ret = tmp + t;
		}
		printf("The shortest path has length %d\n", ret);
	}
	return 0;
}
