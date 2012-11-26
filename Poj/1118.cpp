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

const double eps = 1e-8;
const double inf = 1e10;
struct Point
{
	double x, y;
}p[777], cp[777];
int N;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double cross_product(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(Point a, Point b)
{
	return cross_product(cp[0], a, b) < eps;
}

void solve()
{
	int ans = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cp[j] = p[j];
		}
		swap(cp[0], cp[i]);
		sort(cp + 1, cp + N, cmp);
		for (int j = 1; j < N; j++)
		{
			double ang;
			if (dblcmp(cp[j].x - cp[0].x) != 0)
			{
				ang = (cp[j].y - cp[0].y) / (cp[j].x - cp[0].x);
			}
			else ang = inf;
			int cnt = 2;

			int k;
			for (k = j + 1; k < N; k++, cnt++)
			{
				double tmp;
				if (dblcmp(cp[k].x - cp[0].x) != 0)
				{
					tmp = (cp[k].y - cp[0].y) / (cp[k].x - cp[0].x);
				}
				else tmp = inf;
				if (dblcmp(ang - tmp) != 0) break;
			}
			j = k - 1;
			ans = max(ans, cnt);
		}
	}
	printf("%d\n", ans);
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		for (int i = 0; i < N; i++)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		solve();
	}	
	return 0;
}

