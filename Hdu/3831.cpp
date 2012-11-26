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

const int MAXN = 500 + 10;
int N, M;
int dp[MAXN][MAXN][55], f[MAXN][MAXN];
char src[MAXN], des[MAXN], srcs[MAXN], dess[MAXN];

char tochar(int x)
{
	if (x <= 26) return (char)(x + 'a' - 1);
	else return (char)(x - 27 + 'A');
}

int main()
{
	freopen("a", "r", stdin);
	while (1)
	{
		scanf("%s", srcs);
		if (strcmp(srcs, "#") == 0) break;
		scanf("%s", dess);
		M = strlen(srcs);
		N = strlen(dess);
		for (int i = M; i >= 1; i--)
			src[i] = srcs[i - 1];
		for (int j = N; j >= 1; j--)
			des[j] = dess[j - 1];
		for (int i = 0; i <= M; i++)
		for (int j = 0; j <= N; j++)
		for (int k = 0; k < 53; k++)
			dp[i][j][k] = 1000;
		for (int i = 0; i <= M; i++)
		for (int j = 0; j <= N; j++)
			f[i][j] = 1000;

		for (int i = 0; i <= M; i++)
			f[i][0] = dp[i][0][0] = i;
		for (int j = 1; j <= N; j++)
			f[0][j] = dp[0][j][0] = j;

		int tmp;
		for (int j = 1; j <= N; j++)
		{
			for (int i = 1; i <= M; i++)
			{
				tmp = 1000;
				tmp = min(dp[i - 1][j][0] + 1, dp[i][j - 1][0] + 1);
				if (src[i] == des[j]) tmp = min(tmp, dp[i - 1][j - 1][0]);
				else tmp = min(tmp, dp[i - 1][j - 1][0] + 1);
				dp[i][j][0] = tmp;
				f[i][j] = dp[i][j][0];
				for (int t = 1; t <= 52; t++)
				{
					tmp = 1000;
					tmp = min(dp[i - 1][j][t] + 1, dp[i][j - 1][t] + 1);
					if (tochar(t) == des[j])
					{
						tmp = min(tmp, dp[i - 1][j - 1][t]);
						for (int t1 = i, t2 = j; t1 > 0 && t2 > 0 && des[t2] == des[j];)
						{
							t1--; t2--;
							tmp = min(tmp, f[t1][t2] + 1);
						}
					}
					else
					{
						tmp = min(tmp, dp[i - 1][j - 1][t] + 1);
					}
					dp[i][j][t] = tmp;
					f[i][j] = min(f[i][j], dp[i][j][t]);
				}
			}
		}
		cout << f[M][N] << endl;
	}
	return 0;
}
