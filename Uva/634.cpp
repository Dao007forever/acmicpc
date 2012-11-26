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

const int MAXN = 1111;
const double eps = 1e-8;
struct Point
{
	double x, y;
}P[MAXN];
struct Line
{
	Point a, b;
};
int N;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double cross_product(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
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

bool onEdge(Point pot, Line line)
{
	return dblcmp(cross_product(pot, line.a, line.b)) == 0 &&
		dblcmp((pot.x - line.a.x) * (pot.x - line.b.x)) <= 0 &&
		dblcmp((pot.y - line.a.y) * (pot.y - line.b.y)) <= 0;
}

int isinPolygon(Point A)
{
	if (N == 1) return dblcmp(A.x - P[1].x) == 0 && dblcmp(A.y - P[1].y) == 0;
	if (N == 2)
	{
		Line side;
		side.a = P[1];
		side.b = P[2];
		return onEdge(A, side);
	}
	int cnt = 0;
	Line line;
	line.a = A;
	line.b.y = A.y;
	line.b.x = -1e10;

	P[N + 1] = P[1];
	for (int i = 1; i <= N; i++)
	{
		Line side;
		side.a = P[i];
		side.b = P[i + 1];

		if (onEdge(A, side)) return true;
		if (dblcmp(side.a.y - side.b.y) == 0) continue;

		if (onEdge(side.a, line))
		{
			if (side.a.y > side.b.y)
				cnt++;
		}
		else if (onEdge(side.b, line))
		{
			if (side.b.y > side.a.y)
				cnt++;
		}
		else if (segcross(line.a, line.b, side.a, side.b))
			cnt++;
	}
	return cnt % 2;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		for (int i = 1; i <= N; i++)
			scanf("%lf%lf", &P[i].x, &P[i].y);
		P[N + 1] = P[1];
		Point tmp;
		scanf("%lf%lf", &tmp.x, &tmp.y);
		if (isinPolygon(tmp)) printf("T\n");
		else printf("F\n");
	}
	return 0;
}
