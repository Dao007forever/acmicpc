/*
 * Author: Yang Zhang
 * Created Time: Sun 09 Sep 2012 02:15:43 PM CST
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

#define MAXN 105
const int inf = 1000000000;
int n;
int a[MAXN];
int dp[MAXN][MAXN][MAXN];
int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		scanf("%d", &n);
		printf("Case #%d: ", cas);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}	
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					dp[i][j][k] = inf;
		dp[1][1][1] = 0;
		for (int i = 1; i < n; i++)
			for (int j = 0; j <= i; j++) {
				if (j == 0) {
					if (dp[i][j][0] == inf) continue;
					dp[i + 1][1][i + 1] = min(dp[i + 1][1][i + 1], dp[i][j][0]);
				} else {
					for (int k = 1; k <= i; k++) {
						if (dp[i][j][k] == inf) continue;
						//push
						dp[i + 1][j + 1][i + 1] = min(dp[i + 1][j + 1][i + 1], dp[i][j]);
						//pop
						dp[i + 1][j - 1][k] = min(dp[i + 1][j - 1][k], dp[i][j][k])
					}
				}
			}

		int ret = min(dp[n][1][0], dp[n][n][1]);
		printf("%d\n", ret);
	}
	return 0;
}

