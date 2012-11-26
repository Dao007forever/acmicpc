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

int N, M;
int a[111], b[111], g[111][111], cx[111], cy[111], mk[111];

int path(int u)
{
	for (int v = 1; v <= M; v++)
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
	for (int i = 1; i <= N; i++)
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
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++)
	{
		printf("Case %d: ", cas);
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &a[i]);
		scanf("%d", &M);
		for (int i = 1; i <= M; i++)
			scanf("%d", &b[i]);
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				if (a[i] == 0 && b[j] != 0) g[i][j] = 0;
				else if (a[i] != 0 && b[j] == 0) g[i][j] = 1;
				else if (a[i] == 0 && b[j] == 0) g[i][j] = 1;
				else if (b[j] % a[i] == 0) g[i][j] = 1;
					
		printf("%d\n", MaxMatch());
	}
	return 0;
}
