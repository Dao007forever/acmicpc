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
int N, M, nx, ny, cnt;
int g[MAXN][MAXN], cx[MAXN], cy[MAXN], mk[MAXN], ans[MAXN];
map<int, int> MAP;

int Check(int a, int b)
{
	int temp = ans[a] ^ ans[b];
	if (temp == 0) return 0;
	if ((temp & (temp - 1)) == 0) return 1;
	return 0;
}

int path(int u)
{
	for (int v = 1; v <= ny; v++)
	{
		if (g[u][v] && !mk[v])
		{
			mk[v] = 1;
			if (!cy[v] || path(cy[v]))
			{
				cx[u] = v;
				cy[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int MaxMatch()
{
	int res = 0;
	memset(cx, 0, sizeof(cx));
	memset(cy, 0, sizeof(cy));
	for (int i = 1; i <= nx; i++)
	{
		if (!cx[i])
		{
			memset(mk, 0, sizeof(mk));
			res += path(i);
		}
	}
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		if (N == 0 && M == 0) break;
		if (MAP.size()) MAP.clear();
		char str[MAXN];
		cnt = 0;
		for (int i = 0; i < M; i++)
		{
			scanf("%s", str);
			int sum1 = 0, sum2 = 0;
			for (int j = N - 1; j >= 0; j--)
			{
				if (str[j] == '*')
				{
					sum1 = sum1 * 2 + 1;
					sum2 = sum2 * 2;
				}
				else
				{
					if (str[j] == '1')
					{
						sum1 = sum1 * 2 + 1;
						sum2 = sum2 * 2 + 1;
					}
					else if (str[j] == '0')
					{
						sum1 = sum1 * 2;
						sum2 = sum2 * 2;
					}
				}
			}
			if (MAP.find(sum1) == MAP.end())
			{
				MAP[sum1] = cnt;
				ans[++cnt] = sum1;
			}
			if (MAP.find(sum2) == MAP.end())
			{
				MAP[sum2] = cnt;
				ans[++cnt] = sum2;
			}
		}
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= cnt; i++)
		{
			for (int j = i + 1; j <= cnt; j++)
			{
				if (Check(i, j))
				{
					g[i][j] = g[j][i] = 1;
				}
			}
		}
		nx = cnt;
		ny = cnt;
		printf("%d\n", cnt - MaxMatch() / 2);
	}
	return 0;
}
