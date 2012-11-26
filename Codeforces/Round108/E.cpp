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

const int maxn = 128;
int N, M, K;
int x[maxn], y[maxn], a[maxn][maxn];
int dp[maxn][maxn][maxn], path[maxn][maxn][maxn][3];

void bellman_ford() {
	
}

int main() {
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
			for (int k = 0; k < (1 << K); i++)
				dp[i][j][k] = inf;
	for (int i = 0; i < K; i++) {
		dp[x[i]][y[i]][1 << i] = a[x[i]][y[i]];
		path[x[i]][y[i]][0] = 2;
	}

	for (int mask = 0; mask < (1 << K); mask++) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) {
				for (int mask2 = 0; mask2 < mask; mask2++)
					if (!(~mask & mask2) == 0) {
						if (dp[mask2][i][j] + dp[mask - mask2][i][j] < dp[mask][i][j]) {
							dp[mask][i][j] = dp[mask2][i][j] + dp[mask - mask2][i][j];
							path[mask][i][j] = 1;
							path[mask][i][j] = mask2;
							path[mask][i][j] = mask - mask2;
						}
					}
			}
		bellman_ford(mask);
	}
}
