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

#define REP(i, n) for(i = 0; i < (n); ++i)
#define FOR(i, l, h) for(i = (l); i <= (h); ++i)
#define FORD(i, h, l) for(i = (h); i >= (l); --i)

const int MAXN = 200 + 10;
int T, N, n, res;
int Beat[MAXN][MAXN];
bool dp[MAXN][MAXN], Win[MAXN];

void Init()
{
	memset(dp, 0, sizeof(dp));
	memset(Win, 0, sizeof(Win));
	memset(Beat, 0, sizeof(Beat));
	res = 0;
	scanf("%d", &N);
	int i, j;
	FOR(i, 1, N)
	{
		char str[MAXN] = {0};
		scanf("%s", str);
		int len = strlen(str);
		int j;
		REP(j, len)
		{
			Beat[i][j + 1] = Beat[i][j + 1 + N] = Beat[i + N][j + 1] = Beat[i + N][j + 1 + N] = (str[j] == '1');
		}
	}
	n = 2 * N;
}

void Solve()
{
	int i;
	FOR(i, 1, n - 1)
	{
		dp[i][i + 1] = true;
	}
	int j, l, k;
	FOR(l, 3, N)
	{
		FOR(i, 1, n)
		{
			j = i + l - 1;
			if (j > n) break;
			FOR(k, i + 1, j - 1)
			{
				if (dp[i][k] && dp[k][j] && (Beat[i][k] || Beat[j][k]))
				{
					dp[i][j] = true;
					break;
				}
			}
		}
	}
	FOR(i, 1, N)
	{
		FOR(j, i + 1, i + N)
		{
			if (dp[i][j] && dp[j][i + N] && Beat[i][j])
			{
				res++;
				Win[i] = true;
				break;
			}
		}
	}
	printf("%d\n", res);
	FOR(i, 1, N)
	if (Win[i])
	{
		printf("%d\n", i);
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		Init();
		Solve();
	}
	return 0;
}
