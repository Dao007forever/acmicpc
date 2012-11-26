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
#define abs(x) ((x) > 0 ? (x) : -(x))
int N, chg;
int off = 105;
bool dp[111][55][210][5];
char st[111];

int dir(int d) {
	return d ? 1 : -1;
}

int main()
{
	scanf("%s", st + 1);
	N = strlen(st + 1);
	cin >> chg;
	memset(dp, 0, sizeof(dp));
	dp[0][0][off][1] = 1;
	for (int i = 0; i < N; i++)
		for (int c = 0; c <= chg; c++)
			for (int d = 0; d < 210; d++)
				for (int f = 0; f < 2; f++) 
				if (dp[i][c][d][f]) {
					if (st[i + 1] == 'T') {
						for (int k = c; k <= chg; k++)
							if ((k - c) & 1)
								dp[i + 1][k][d + dir(f)][f] = 1;
							else dp[i + 1][k][d][f ^ 1] = 1;
					} else {
						for(int k = c; k <= chg; k++)
							if (!((k - c) & 1))
								dp[i + 1][k][d + dir(f)][f] = 1;
							else dp[i + 1][k][d][f ^ 1] = 1;
					}
				}
	int ret = 0;
	for (int i = 0; i < 210; i++)
		if (dp[N][chg][i][0] || dp[N][chg][i][1])
			ret = max(ret, abs(i - off));
	cout << ret << endl;
	return 0;
}
