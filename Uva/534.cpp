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

const int MAXN = 222;
const double eps = 1e-6;
struct Point
{
	double x, y;
}P[MAXN];
int N;
bool vis[MAXN][MAXN];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double dist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool Check(double limit)
{
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (i != j)
	{
		if (dblcmp(limit - dist(P[i], P[j])) >= 0) vis[i][j] = 1;
	}
	
	for (int k = 1; k <= N; k++)
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (i != j && i != k && j != k)
		if (!vis[i][j] && vis[i][k] && vis[k][j])
			vis[i][j] = 1;
	return vis[1][2];
}

int main()
{
	freopen("a", "r", stdin);
	int cas = 0;
	while (scanf("%d", &N) && N)
	{
		printf("Scenario #%d\n", ++cas);
		for (int i = 1; i <= N; i++)
		{
			scanf("%lf%lf", &P[i].x, &P[i].y);
		}
		double Left = 0.0, Right = 10000.0;
		while (Left < Right - eps)
		{
			double Mid = (Left + Right) / 2.0;
			if (Check(Mid)) Right = Mid;
			else Left = Mid;
		}
		printf("Frog Distance = %.3lf\n", Left);
		puts("");
	}
	return 0;
}
