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

const int MAXN = 1000 + 10;
const double eps = 1e-8;
struct Point
{
	double x, y;
};
struct Segment
{
	Point a, b;
};
int p[MAXN];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double cross(Point a, Point b, Point c)
{
	return ((c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y));
}

int xyCmp(double p, double mini,double maxi)
{
	return dblcmp(p - mini) * dblcmp(p - maxi);
}

int betweenCmp(Point a, Point b, Point c)
{
	if (fabs(b.x - c.x) > fabs(b.y - c.y))
		return xyCmp(a.x, min(b.x, c.x), max(b.x, c.x));
	else return xyCmp(a.y, min(b.y, c.y), max(b.y, c.y));
}

int segcross(Point a, Point b, Point c, Point d)
{
	double s1, s2, s3, s4;
	int d1, d2, d3, d4;
	d1 = dblcmp(s1 = cross(a, b, c));
	d2 = dblcmp(s2 = cross(a, b, d));
	d3 = dblcmp(s3 = cross(c, d, a));
	d4 = dblcmp(s4 = cross(c, d, b));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 1;
	
	if (d1 == 0 && betweenCmp(c, a, b) <= 0 ||
		d2 == 0 && betweenCmp(d, a, b) <= 0 ||
		d3 == 0 && betweenCmp(a, c, d) <= 0 ||
		d4 == 0 && betweenCmp(b, c, d) <= 0)
		return 1;
	return 0;
}

int find(int x)
{
	if (p[x] != x)
		p[x] = find(p[x]);
	return p[x];
}

void Union(int x, int y)
{
	p[find(x)] = find(y);
}

int main()
{
	freopen("a", "r", stdin);
	int N;
	Segment seg[MAXN];
	while (scanf("%d", &N) != EOF && N)
	{
		for (int i = 1; i <= N; i++)
		{
			scanf("%lf%lf%lf%lf", &seg[i].a.x, &seg[i].a.y, &seg[i].b.x, &seg[i].b.y);
		}
		for (int i = 1; i <= N; i++)
			p[i] = i;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			if (i != j)
			{
				if (segcross(seg[i].a, seg[i].b, seg[j].a, seg[j].b) == 1)
				{
					Union(i, j);
				}
			}
		}
		int a, b;
		while (scanf("%d%d", &a, &b) == 2)
		{
			if (a == 0 && b == 0) break;
			if (find(a) == find(b))
			{
				printf("CONNECTED\n");
			}
			else
			{
				printf("NOT CONNECTED\n");
			}
		}
	}
	return 0;
}
