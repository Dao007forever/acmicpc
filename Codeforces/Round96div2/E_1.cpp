#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstdio>
#include <cstring>
using namespace std;

bool dp[105][55][210][2];
char com[105], n;
int chg, off = 105;

int dir(int d) {
	return d ? 1 : -1;
}

int main() {
	freopen("in", "r", stdin);
	cin >> com + 1;
	n = strlen(com + 1);
	cin >> chg;
	memset(dp, false, sizeof(dp));
	dp[0][0][off][1] = true;
	for (int i = 0; i < n; i++) for (int c = 0; c <= chg; c++)
	for (int d = 0; d < 210; d++) for (int f = 0; f < 2; f++) 
	if (dp[i][c][d][f]) {
		if (com[i + 1] == 'T') {
			for (int k = c; k <= chg; k++) {
				if ((k - c) & 1)
					dp[i + 1][k][d + dir(f)][f] = true;
				else
					dp[i + 1][k][d][f ^ 1] = true;
			}
		} else {
			for (int k = c; k <= chg; k++) {
				if (!((k - c) & 1))
					dp[i + 1][k][d + dir(f)][f] = true;
				else
					dp[i + 1][k][d][f ^ 1] = true;
			}
		} 
	}
	int res = 0;
	for (int i = 0; i < 210; i++) 
	if (dp[n][chg][i][0] || dp[n][chg][i][1])
		 res = max(res, abs(i - off));
	cout << res << endl;
	return 0;
}


