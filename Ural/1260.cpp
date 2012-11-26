/*
 *  求1～N的一种合法的排列是第一个数为1，后面妹两个相邻的数的差不超过2，求这样的方案数
 *  如果要放数i+1，那么它肯定只能放在i或者i-1的两边，用f(i,j,k)表示当前放第i个数，i-1在位置j，i在位置k的方案数
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

int n;
int dp[66][66][66];

int main()
{
	cin >> n;
	memset(dp, 0, sizeof(dp));
	for (int i = 2; i <= n; i++)
		dp[2][i][1] = 1;
	for (int i = 2; i < n; i++) {
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				if (dp[i][j][k]) {
					int t[5] = {0};
					t[0] = j - 1; t[1] = j + 1; t[2] = k - 1; t[3] = k + 1;
					sort(t, t + 4);
					unique(t, t + 4);
					int m = 4;
					for (int l = 0; l < 4; l++)
						if (t[l] == t[l + 1]) {
							m = l;
							break;
						}
					for (int l = 0; l < m; l++)
						if (t[l] > 1 && t[l] <= n && t[l] != j && t[l] != k) {
							if (t[l] == 2 && i + 1 > 3) continue;
							dp[i + 1][t[l]][j] += dp[i][j][k];
						}
				}
	}
	for (int k = 2; k <= n; k++) {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (dp[k][i][j])
				cout << i << " " << j << " " << dp[k][i][j] << endl;
	cout << endl;
	}
	cout << endl;
	int ret = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (dp[n][i][j]) {
				ret += dp[n][i][j];
			}
	cout << ret << endl;
	return 0;
}
