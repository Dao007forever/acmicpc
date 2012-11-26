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

int T;
int N, K;
long long dp[1000][20];

int POW(int k, int P)
{
	int res = 1;
	for (int i = 1; i <= k; i++)
	{
		res *= 10;
		res %= P;
	}
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &K);
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < 10; i++)
		{
			dp[i % N][1]++;
		}
		for (int i = 0; i < 10; i++)
		{
			int temp = (i + 10 * i) % N;
			dp[temp][2]++;
		}
		for (int k = 3; k <= K; k++)
		{
			for (int r = 0; r < N; r++)
			{
				for (int i = 0; i < 10; i++)
				{
					if (k == K && i == 0) continue;
					int temp = POW(k - 1, N);
					int p = (r * 10 + i + i * temp) % N;
					dp[p][k] += dp[r][k - 2];
				}
			}
		}
		if (K <= 2) dp[0][K]--;
		cout << dp[0][K] << endl;
	}
	return 0;
}
