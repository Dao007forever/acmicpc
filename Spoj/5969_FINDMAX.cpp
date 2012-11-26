/*
 * Author: Yang Zhang
 * Created Time: Tue 28 Aug 2012 10:55:07 PM CST
 * File Name: 5969_FINDMAX.cpp
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

const int N = 100, K = 300, mod = 1000000007;
int dp[105][105][305], sum[105][105][305];

int main() {
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= K; i++)
		dp[1][1][i] = 1, sum[1][1][i] = sum[1][1][i - 1] + dp[1][1][i];
	for (int i = 2; i <= N; i++)
		for (int j = 1; j <= i; j++)
			for (int k = 1; k <= K; k++) {
				dp[i][j][k] = ((LL)dp[i - 1][j][k] * k) % mod;
				dp[i][j][k] = (dp[i][j][k] + sum[i - 1][j - 1][k - 1]) % mod;
				sum[i][j][k] = (sum[i][j][k - 1] + dp[i][j][k]) % mod;
			}
	int Test;
	scanf("%d", &Test);
	for (; Test--; ) {
		int n, k, p;
		scanf("%d%d%d", &n, &k, &p);
		int ret = 0;
		for (int i = 1; i <= k; i++)
			ret = (ret + dp[n][p + 1][i]) % mod;
		printf("%d\n", ret);
	}
	return 0;
}

