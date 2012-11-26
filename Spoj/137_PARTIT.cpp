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

int N, M, K;
int dp[11][222][222];
//vector<int> ans;
int ans[222], sp;

void DP(int x, int y, int z) {
	if (x == N && y == M) {
		dp[x][y][z] = 1;
		return;
	}
	if (x == N || y == M) {
		dp[x][y][z] = 0;
		return;
	}
	dp[x][y][z] = 0;
	for (int i = z; y + i <= M; i++) {
		if (dp[x + 1][y + i][i] == -1)
			DP(x + 1, y + i, i);
		dp[x][y][z] += dp[x + 1][y + i][i];
	}
}

void dfs(int x, int y, int z, int k) {
	if (x == N || y == M) return;
	for (int i = z; y + i <= M; i++) {
		if (dp[x + 1][y + i][i] > k) {
			//ans.PB(i);
			ans[sp++] = i;
			dfs(x + 1, y + i, i, k);
			return;
		} else {
			k -= dp[x + 1][y + i][i];
		}
	}
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		//ans.clear();
		cin >> M >> N >> K;
		K--;
		memset(dp, -1, sizeof(dp));
		DP(0, 0, 1);
		sp = 0;
		dfs(0, 0, 1, K);
		for (int i = 0; i < sp; i++)
			printf("%d%c", ans[i], i == sp - 1 ? '\n' : ' ');
	}
	return 0;
}
