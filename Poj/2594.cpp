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
int N, M, res;
int g[MAXN][MAXN], mate[MAXN], mk[MAXN];

int path(int u)
{
	for (int v = 1; v <= N; v++)
	{
		if (!mk[v] && g[u][v])
		{
			mk[v] = 1;
			if (!mate[v] || path(mate[v]))
			{
				mate[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

void MaxMatch()
{
	memset(mate, 0, sizeof(mate));
	for (int i = 1; i <= N; i++)
	{
		memset(mk, 0, sizeof(mk));
		res += path(i);
	}
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		if (N == 0 && M == 0) break;
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			g[u][v] = 1;
		}
		for (int k = 1; k <= N; k++)
			for (int i = 1; i <= N; i++)
				for (int j = 1; j <= N; j++)
					if (g[i][k] && g[k][j])
						g[i][j] = 1;

		res = 0;
		MaxMatch();
		printf("%d\n", N - res);
	}
	return 0;
}
