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
struct Point
{
	int x, y;
}S[MAXN], E[MAXN];
int N, hour, minute, st[MAXN], en[MAXN], g[MAXN][MAXN], res;
int cx[MAXN], cy[MAXN], mk[MAXN];

int path(int u)
{
	for (int v = 1; v <= N; v++)
	{
		if (!mk[v] && g[u][v])
		{
			mk[v] = 1;
			if (!cy[v] || path(cy[v]))
			{
				cy[v] = u;
				cx[u] = v;
				return 1;
			}
		}
	}
	return 0;
}

int MaxMatch()
{
	res = 0;
	memset(cx, 0, sizeof(cx));
	memset(cy, 0, sizeof(cy));
	for (int i = 1; i <= N; i++)
	if (!cx[i])
	{
		memset(mk, 0, sizeof(mk));
		res += path(i);
	}
}

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		memset(g, 0, sizeof(g));
		memset(en, 0, sizeof(en));
		memset(st, 0, sizeof(st));
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			scanf("%d:%d", &hour, &minute);
			scanf("%d%d%d%d", &S[i].x, &S[i].y, &E[i].x, &E[i].y);
			st[i] = 60 * hour + minute;
			en[i] = st[i] + fabs(S[i].x - E[i].x) + fabs(S[i].y - E[i].y);
		}
		for (int i = 1; i <= N; i++)
			for (int j = i + 1; j <= N; j++)
			{
				int dis = fabs(S[j].x - E[i].x) + fabs(S[j].y - E[i].y);
				if (en[i] + dis + 1 <= st[j]) g[i][j] = 1;
			}

		MaxMatch();
		printf("%d\n", N - res);
	}
	return 0;
}
