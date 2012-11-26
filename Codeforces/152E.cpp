/*
 * 斯坦納树，最短路+状压dp
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

#define inf (1 << 29)
const int maxn = 128;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int N, M, K;
int x[maxn], y[maxn], a[maxn][maxn];
int dp[maxn][maxn][maxn], path[maxn][maxn][maxn][3];
string ans[maxn];

void bellman_ford(int mask) {
	for (int iter = 0; iter < N * M + 10; iter++) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) 
				for (int k = 0; k < 4; k++) {
					int xx = i + dx[k], yy = j + dy[k];
					if (xx >= 0 && xx < N && yy >= 0 && yy < M) {
						int tmp = dp[i][j][mask] + a[xx][yy];
						if (tmp < dp[xx][yy][mask]) {
							dp[xx][yy][mask] = tmp;
							path[xx][yy][mask][0] = 0;
							path[xx][yy][mask][1] = i;
							path[xx][yy][mask][2] = j;
						}
					}
				}
	}	
}

void Print(int xx, int yy, int mask) {
	ans[xx][yy] = 'X';
	if (path[xx][yy][mask][0] == 0) Print(path[xx][yy][mask][1], path[xx][yy][mask][2], mask);
	if (path[xx][yy][mask][0] == 1) {
		Print(xx, yy, path[xx][yy][mask][1]);
		Print(xx, yy, path[xx][yy][mask][2]);
	}
}

int main() {
	freopen("in", "r", stdin);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> a[i][j];
	for (int i = 0; i < K; i++) {
		cin >> x[i] >> y[i];
		x[i]--; y[i]--;
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			for (int k = 0; k < (1 << K); k++)
				dp[i][j][k] = inf;
	for (int i = 0; i < K; i++) {
		dp[x[i]][y[i]][1 << i] = a[x[i]][y[i]];
		path[x[i]][y[i]][1 << i][0] = 2;
	}

	for (int mask = 0; mask < (1 << K); mask++) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) {
				for (int mask2 = 0; mask2 < mask; mask2++)
					if (!(~mask & mask2)) {
						int tmp = dp[i][j][mask2] + dp[i][j][mask - mask2] - a[i][j];
						if (tmp < dp[i][j][mask]) {
							dp[i][j][mask] = tmp;
							path[i][j][mask][0] = 1;
							path[i][j][mask][1] = mask2;
							path[i][j][mask][2] = mask - mask2;
						}
					}
			}
		bellman_ford(mask);
	}
	int ret = inf;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			ret = min(ret, dp[i][j][(1 << K) - 1]);
		}
	cout << ret << endl;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			ans[i] += '.';
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (dp[i][j][(1 << K) - 1] == ret) {
				Print(i, j, (1 << K) - 1);
				for (int k = 0; k < N; k++)
					cout << ans[k] << endl;
				return 0;
			}
	return 0;
}
