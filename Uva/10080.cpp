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
double s, v;
int g[111][111], cx[111], cy[111], mk[111];
double px[111], py[111], gx[111], gy[111];

int path(int u)
{
	for (int v = 1; v <= M; v++)
	{
		if (g[u][v] > 0 && (!mk[v]))
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

double dist(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d%lf%lf", &N, &M, &s, &v) != EOF)
	{
		for (int i = 1; i <= N; i++)
			scanf("%lf%lf", &px[i], &py[i]);
		for (int i = 1; i <= M; i++)
			scanf("%lf%lf", &gx[i], &gy[i]);
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
			{
				if (dist(px[i], py[i], gx[j], gy[j]) / v < s)
					g[i][j] = 1;
			}
		printf("%d\n", N - MaxMatch());
	}
	return 0;
}
