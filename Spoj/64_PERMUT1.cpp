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

int n, k, n2;
int dp[1 << 15][99];

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d", &n, &k);
		memset(dp, 0, sizeof(dp));
		dp[0][k] = 1;
		n2 = (1 << n);
		for (int i = 0; i < n2; i++)
			for (int j = k; j >= 0; j--)
			{
				int s = 0;
				for (int l = n - 1; j - s >= 0 && l >= 0; l--)
				if (i & (1 << l))
				{
					s++;
				}
				else
				{
					dp[i | (1 << l)][j - s] += dp[i][j];
				}
			}
		printf("%d\n", dp[n2 - 1][0]);
	}
	return 0;
}
