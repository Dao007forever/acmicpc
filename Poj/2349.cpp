#include <set>
#include <map>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
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
const double INF = 1e10;
int T, S, P;
int cnt;
double g[MAXN][MAXN], dis[MAXN], E[MAXN];
int use[MAXN];
struct Node
{
	double x, y;
}Po[MAXN];
struct Point
{
	int u;
	double d;
	bool operator <(const Point it)const
	{
		return d > it.d;
	}
};

double dist(int a, int b)
{
	double x = Po[a].x - Po[b].x, y = Po[a].y - Po[b].y;
	return sqrt(x * x + y * y);
}

priority_queue<Point> Q;
void Prim(int u)
{
	for (int i = 1; i <= P; i++)
	{
		use[i] = 0;
		dis[i] = INF;
	}
	dis[u] = 0;
	use[u] = 1;
	for (int i = 1; i <= P; i++)
	if (i != u)
	{
		dis[i] = g[u][i];
	}
	for (int k = 1; k < P; k++)
	{
		double Min = INF;
		for (int i = 1; i <= P; i++)
		if (!use[i] && dis[i] < Min)
		{
			Min = dis[i];
			u = i;
		}
		use[u] = 1;
		E[cnt++] = dis[u];
		for (int i = 1; i <= P; i++)
		{
			if (!use[i] && g[u][i] < dis[i])
			{
				dis[i] = g[u][i];
			}
		}
	}
}

int main()
{
	freopen("a.txt", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		memset(g, 0, sizeof(g));
		memset(E, 0, sizeof(E));
		scanf("%d%d", &S, &P);
		for (int i = 1; i <= P; i++)
		{
			scanf("%lf%lf", &Po[i].x, &Po[i].y);
		}
		for (int i = 1; i < P; i++)
		for (int j = i + 1; j <= P; j++)
			g[i][j] = g[j][i] = dist(i, j);
		cnt = 0;
		Prim(1);
		sort(E, E + cnt);
		printf("%.2lf\n", E[P - S - 1]);
	}
	return 0;
}
