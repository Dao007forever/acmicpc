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
int nx, ny, res;
int g[MAXN][MAXN], cx[MAXN], cy[MAXN], mk[MAXN];

int path(int u)
{
	for (int v = 1; v <= ny; v++)
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

int MaxMatch()
{
	res = 0;
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
	while (scanf("%d", &nx) && nx)
	{
		scanf("%d", &ny);
		for (int i = 1; i <= nx; i++)
			for (int j = 1; j <= ny; j++)
				scanf("%d", &g[i][j]);
		printf("%d\n", MaxMatch());
	}
	return 0;
}
