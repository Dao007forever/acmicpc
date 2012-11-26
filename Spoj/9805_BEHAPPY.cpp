/*
 * Author: Yang Zhang
 * Created Time: Sun 19 Aug 2012 10:13:58 AM UTC
 * File Name: 9805_BEHAPPY.cpp
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

int n, m;
int a[111], b[111];
LL dp[11][111];
int main() {
	while (~scanf("%d%d", &m, &n)) {
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &a[i], &b[i]);
			if (a[i] > b[i]) swap(a[i], b[i]);
		}
		memset(dp, 0, sizeof(dp));
		for (int j = a[1]; j <= min(b[1], n); j++)
			dp[1][j] = 1;
		for (int i = 2; i <= m; i++)
			for (int j = 0; j <= n; j++) {
				if (j - a[i] < 0) continue;
				for (int k = max(0, j - b[i]); k <= max(0, j - a[i]); k++)
					dp[i][j] += dp[i - 1][k];
			}
		cout << dp[m][n] << endl;
	}
	return 0;
}

