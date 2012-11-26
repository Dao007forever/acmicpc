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

const int MAXN = 100 + 10;
const int MAXM = 70;
int N, M;
int dp[MAXN][MAXM][MAXN], sta[MAXN], cur[MAXN], num[MAXN];

bool check(int x)
{
	if (x & (x << 1)) return 0;
	if (x & (x << 2)) return 0;
	return 1;
}

bool fit(int x, int k)
{
	if (cur[k] & x) return 0;
	return 1;
}

int Count(int x)
{
	int cnt = 0;
	while (x)
	{
		cnt++;
		x &= (x - 1);
	}
	return cnt;
}

int main()
{
	freopen("a", "r", stdin);
	cin >> N >> M;
	int top = 0, total = 1 << M;
	for (int i = 0; i < total; i++)
		if (check(i)) sta[++top] = i;
	char str[MAXN][MAXN];
	for (int i = 1; i <= N; i++)
	{
		scanf("%s", str[i] + 1);
		cur[i] = 0;
		for (int j = 1; j <= M; j++)
		{
			if (str[i][j] == 'H') cur[i] += (1 << (j - 1));
		}
	}

	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= top; i++)
	{
		num[i] = Count(sta[i]);
		if (fit(sta[i], 1)) dp[1][1][i] = num[i];
	}

	for (int i = 2; i <= N; i++)
	{
		for (int t = 1; t <= top; t++)
		{
			if (!fit(sta[t], i)) continue;
			for (int j = 1; j <= top; j++)
			{
				if (sta[t] & sta[j]) continue;
				for (int k = 1; k <= top; k++)
				{
					if (sta[t] & sta[k]) continue;
					if (dp[i - 1][j][k] == -1) continue;
					dp[i][k][t] = max(dp[i][k][t], dp[i - 1][j][k] + num[t]);
				}
			}
		}
	}
	int res = 0;
	for (int i = 1; i <= top; i++)
	for (int j = 1; j <= top; j++)
		res = max(res, dp[N][i][j]);
	cout << res << endl;
	return 0;
}
