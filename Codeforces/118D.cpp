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

const int Mod = 100000000;
int n1, n2, k1, k2;
int dp[111][111][11][11];

inline void add(int &res, int plus)
{
	res = (res + plus) % Mod;
}

int main()
{
	freopen("a", "r", stdin);
	int ans = 0;
	scanf("%d%d%d%d", &n1, &n2, &k1, &k2);
	dp[0][0][0][0] = 1;
	for (int i1 = 0; i1 <= n1; i1++)
		for (int i2 = 0; i2 <= n2; i2++)
			for (int j1 = 0; j1 <= k1; j1++)
				for (int j2 = 0; j2 <= k2; j2++)
				{
					if (dp[i1][i2][j1][j2] == 0) continue;
					if (i1 + 1 <= n1 && j1 + 1 <= k1)
						add(dp[i1 + 1][i2][j1 + 1][0], dp[i1][i2][j1][j2]);
					if (i2 + 1 <= n2 && j2 + 1 <= k2)
						add(dp[i1][i2 + 1][0][j2 + 1], dp[i1][i2][j1][j2]);
					if (i1 == n1 && i2 == n2)
						add(ans, dp[i1][i2][j1][j2]);
				}
	printf("%d\n", ans);
	return 0;
}
