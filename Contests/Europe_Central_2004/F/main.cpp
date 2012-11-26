/*
 * Author: Yang Zhang
 * Created Time: Sun 01 Jul 2012 02:42:05 PM UTC
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
const double inf = 1e10;
struct node {
	int x, c, d;

	bool operator < (const node &tp) const {
		return x < tp.x;
	}
}p[MAXN];
double dp[MAXN][MAXN][2];
double sum[MAXN];
int n, v, start;

int main() {
	while (scanf("%d%d%d", &n, &v, &start) && n && v && start) {
		double ret = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d%d", &p[i].x, &p[i].c, &p[i].d);
			ret += p[i].c;
		}
		sort(p + 1, p + n + 1);

		sum[0] = 0;
		for (int i = 1; i <= n; i++)
			sum[i] = sum[i - 1] + (double)p[i].d / v;

		for (int i = 1; i <= n; i++)
			for (int j = i; j <= n; j++)
				dp[i][j][0] = dp[i][j][1] = inf;

		for (int i = 1; i <= n; i++)
			dp[i][i][0] = dp[i][i][1] = fabs((double)start - p[i].x) * sum[n];

		for (int i = n; i >= 1; i--)
			for (int j = i; j <= n; j++)
				for (int k = 0; k <= 1; k++) {
					double x = k ? p[j].x : p[i].x;
					double s = sum[n] - sum[j] + sum[i - 1];
					if (i > 1) {
						dp[i - 1][j][0] = min(dp[i - 1][j][0], dp[i][j][k] + fabs(x - p[i - 1].x) * s);
					}
					if (j < n) {
						dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][k] + fabs(x - p[j + 1].x) * s);
					}
				}
		ret += min(dp[1][n][0], dp[1][n][1]);
		printf("%d\n", (int)ret);
	}
	return 0;
}

