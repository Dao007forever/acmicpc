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
int N;
int res;
int cx[MAXN], cy[MAXN];
int g[MAXN][MAXN];
int mk[MAXN];

int path(int u)
{
	for (int v = 0; v < N; v++)
	{
		if (g[u][v] > 0 && !mk[v])
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

void MaxMatch()
{
	res = 0;
	memset(cx, 0, sizeof(cx));
	memset(cy, 0, sizeof(cy));
	for (int i = 0; i < N; i++)
	{
		if (!cx[i])
		{
			memset(mk, 0, sizeof(mk));
			res += path(i);
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	while(scanf("%d", &N) != EOF)
	{
		memset(mk, 0, sizeof(mk));
		memset(g, 0, sizeof(g));
		for (int i = 0; i < N; i++)
		{
			int u, num, v;
			char ch1, ch2;
			scanf("%d:%c", &u, &ch1);
			scanf("%c%d%c", &ch1, &num, &ch2);
			for (int j = 1; j <= num; j++)
			{
				scanf("%d", &v);
				g[u][v] = 1;
			}
		}
		MaxMatch();
		printf("%d\n", N - res / 2);
	}
	return 0;
}
