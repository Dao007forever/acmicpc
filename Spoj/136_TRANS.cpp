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

const int inf = 100000;
int n, m, u, v;
int dp[55][55], able[33][55][55];
int a[33], b[33], c[33], d[33];
int A[55], B[55];

void check(int now, int l, int r) {
	if (able[now][l][r] != -1) return;

	able[now][l][r] = inf;
	if (r == l && B[l] == now) {
		able[now][l][r] = 0;
		return;
	}

	for (int i = 0; i < v; i++)
		if (a[i] == now) {
			if (i < u) {
				for (int j = l; j < r; j++) {
					if (able[b[i]][l][j] == -1)
						check(b[i], l, j);
					if (able[c[i]][j + 1][r] == -1)
						check(c[i], j + 1, r);
					able[now][l][r] = min(able[now][l][r], able[b[i]][l][j] + able[c[i]][j + 1][r] + 1);
				}
			} else {
				for (int j = l; j < r; j++) {
					if (able[b[i]][l][j] == -1)
						check(b[i], l, j);
					for (int k = j + 1; k < r; k++) {
						if (able[c[i]][j + 1][k] == -1)
							check(c[i], j + 1, k);
						if (able[d[i]][k + 1][r] == -1)
							check(d[i], k + 1, r);
						able[now][l][r] = min(able[now][l][r], able[b[i]][l][j] + able[c[i]][j + 1][k] + able[d[i]][k + 1][r] + 1);
					}
				}
			}
		}
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> n >> m >> u >> v;
		for (int i = 0; i < n; i++)
			cin >> A[i];
		for (int i = 0; i < m; i++)
			cin >> B[i];
		for (int i = 0; i < v; i++)
			if (i < u) {
				cin >> a[i] >> b[i] >> c[i];
			} else {
				cin >> a[i] >> b[i] >> c[i] >> d[i];
			}
		memset(dp, -1, sizeof(dp));
		memset(able, -1, sizeof(able));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				for (int k = 0; k < m; k++)
					check(A[i], j, k);

		dp[0][0] = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) 
				if (dp[i][j] > -1) {
					for (int k = j; k < m; k++) {
						if (able[A[i]][j][k] != inf && dp[i + 1][k + 1] == -1 || dp[i][j] + able[A[i]][j][k] < dp[i + 1][k + 1])
							dp[i + 1][k + 1] = dp[i][j] + able[A[i]][j][k];
					}
				}
		cout << dp[n][m] << endl;
	}
	return 0;
}
