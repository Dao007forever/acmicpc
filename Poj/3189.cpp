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

const int MAXN = 1001;
const int MAXM = 21;
int N, B, n, m, l, r;
int Map[MAXN][MAXM], match[MAXM][MAXN], mk[MAXM], cap[MAXM], c[MAXM];

int dfs(int p)
{
	for (int i = 1; i <= m; i++)
	{
		if (l <= Map[p][i] && Map[p][i] <= r && !mk[i])
		{
			mk[i] = 1;
			if (cap[i])
			{
				cap[i]--;
				match[i][++match[i][0]] = p;
				return 1;
			}
			else
			{
				for (int j = 1; j <= match[i][0]; j++)
				{
					if (dfs(match[i][j]))
					{
						match[i][j] = p;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int MaxMatch()
{
	int ans = 0;
	memset(match, 0, sizeof(match));
	for (int i = 1; i <= n; i++)
	{
		memset(mk, 0, sizeof(mk));
		ans += dfs(i);
	}
	return ans;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &N, &B);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= B; j++)
		{
			int x;
			scanf("%d", &x);
			Map[i][x] = j;
		}
	for (int j = 1; j <= B; j++)
		scanf("%d", &c[j]);

	l = r = 1;
	int ans = B + 1;
	while (l <= r && r <= B)
	{
		for (int i = 1; i <= B; i++)
			cap[i] = c[i];
		n = N; m = B;
		if (MaxMatch() == N)
		{
			if (r - l + 1 < ans) ans = r - l + 1;
			l++;
		}else r++;
	}
	printf("%d\n", ans);
}
