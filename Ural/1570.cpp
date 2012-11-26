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

#define MAXN 105
#define MAXM 20005
const double eps = 1e-8;
int n, m;
struct Dist {
	string name;
	int p, w;
	int vis, num;
}D[MAXN];
int dp[MAXN][MAXM];
int g[MAXN][MAXM], pre[MAXN][MAXM];

void output(int a, int b) {
	if (a == 0) return;
	if (pre[a][b] < b) {
		D[a].vis = 1;
		if ((b - pre[a][b]) % D[a].w == 0)
			D[a].num = (b - pre[a][b]) / D[a].w;
		else D[a].num = (b - pre[a][b]) / D[a].w + 1;
	}
	output(a - 1, pre[a][b]);
}

int main() {
	freopen("in", "r", stdin);
	double x;
	cin >> n >> x;
	m = (int)(1000 * x + eps);
	for (int i = 1; i <= n; i++) {
		double x;
		cin >> D[i].name >> D[i].p >> x;
		D[i].w = (int)(1000 * x + eps);
		D[i].vis = 0;
	}

	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	g[0][0] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= m; j++)
			if (dp[i][j] >= 0) {
				int k;
				for (k = 0; j + k * D[i + 1].w <= m; k++) {
					if (dp[i + 1][j + k * D[i + 1].w] == -1 || dp[i][j] + k * D[i + 1].p < dp[i + 1][j + k * D[i + 1].w]) {
						dp[i + 1][j + k * D[i + 1].w] = dp[i][j] + k * D[i + 1].p;
						pre[i + 1][j + k * D[i + 1].w] = j;
						if (k) g[i + 1][j + k * D[i + 1].w] = g[i][j] + 1;
						else g[i + 1][j + k * D[i + 1].w] = g[i][j];
					} else if (dp[i][j] + k * D[i + 1].p == dp[i + 1][j + k * D[i + 1].w]) {
						if (k && g[i][j] + 1 > g[i + 1][j + k * D[i + 1].w]) {
							g[i + 1][j + k * D[i + 1].w] = g[i][j] + 1;
							pre[i + 1][j + k * D[i + 1].w] = j;
						}
					}
				}

				if (j + k * D[i + 1].w > m) {
					if (dp[i + 1][m] == -1 || dp[i][j] + k * D[i + 1].p < dp[i + 1][m]) {
						dp[i + 1][m] = dp[i][j] + k * D[i + 1].p;
						pre[i + 1][m] = j;
						g[i + 1][m] = g[i][j] + 1;
					} else if (dp[i][j] + k * D[i + 1].p == dp[i + 1][m]) {
						if (g[i][j] + 1 > g[i + 1][m]) {
							g[i + 1][m] = g[i][j] + 1;
							pre[i + 1][m] = j;
						}
					}
				}
			}

	cout << dp[n][m] << endl;
	output(n, m);
	for (int i = 1; i <= n; i++)
		if (D[i].vis) {
			cout << D[i].name << " " << D[i].num << endl;
		}
	return 0;
}
