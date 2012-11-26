/*
 * Author: Yang Zhang
 * Created Time: Mon 10 Sep 2012 04:40:15 PM CST
 * File Name: 6824_CTFLAG.cpp
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

const int len = 26;
int n, m;
int dp[505][26][26], cost[505][26][26], even[26], odd[26];
char st[505][505];

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++)
			scanf("%s", st[i]);
		memset(dp, 63, sizeof(dp));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < len; j++) even[j] = odd[j] = 0;
			for (int j = 0; j < m; j++)
				for (int k = 0; k < len; k++)
					if (st[i][j] != 'a' + k) {
						if (j & 1) odd[k]++;
						else even[k]++;
					}
			for (int j = 0; j < len; j++)
				for (int k = 0; k < len; k++) {
					cost[i][j][k] = even[j] + odd[k];
					if (i == 0 && j != k) dp[i][j][k] = cost[i][j][k];
				}
		}

		for (int i = 0; i < n - 1; i++) {
			int besta = 0, bestb = 1;
			for (int a1 = 0; a1 < len; a1++)
				for (int b1 = 0; b1 < len; b1++) 
					if (dp[i][a1][b1] < dp[i][besta][bestb]) {
						besta = a1; bestb = b1;
					}

			for (int a2 = 0; a2 < len; a2++)
				for (int b2 = 0; b2 < len; b2++) {
					if (a2 == b2) continue;
					if (besta != a2 && bestb != b2) {
						dp[i + 1][a2][b2] = dp[i][besta][bestb] + cost[i + 1][a2][b2];
					} else {
						for (int a1 = 0; a1 < len; a1++)
							for (int b1 = 0; b1 < len; b1++) {
								if (a1 == a2 || b1 == b2 || dp[i][a1][b1] == 0x3f3f3f3f) continue;
								dp[i + 1][a2][b2] = min(dp[i + 1][a2][b2], dp[i][a1][b1] + cost[i + 1][a2][b2]);
							}
					}
				}
			}
		int ret = 0x3f3f3f3f;
		for (int i = 0; i < len; i++)
			for (int j = 0; j < len; j++)
				ret = min(ret, dp[n - 1][i][j]);
		printf("%d\n", ret);
	}
}

