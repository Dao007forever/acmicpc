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

const int MAXN = 2000 + 10;
const int inf = 1000000000;
int N, K;
int w[MAXN], dp[MAXN][MAXN / 2];

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &K) != EOF)
	{
		for (int i = 1; i <= N; i++)
			scanf("%d", &w[i]);
		sort(w + 1, w + N + 1);

		for (int i = 0; i <= N; i++)
		{
			for (int j = 0; j <= K; j++)
			{
				dp[i][j] = inf;
			}
			dp[i][0] = 0;
		}

		for (int i = 2; i <= N; i++)
		{
			for (int j = 1; j * 2 <= i; j++)
			{
				int tmp = (w[i] - w[i - 1]) * (w[i] - w[i - 1]);
				dp[i][j] = min(dp[i - 1][j], dp[i - 2][j - 1] + tmp);
			}
		}
		cout << dp[N][K] << endl;
	}
	return 0;
}
