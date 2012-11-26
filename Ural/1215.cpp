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
const double eps = 1e-8;
struct Point
{
	double x, y;
}P[MAXN];
int N;
Point sta;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double Dot_product(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}

double cross_product(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double Distance(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int xyCmp(double p, double mini, double maxi)
{
    return dblcmp(p - mini) * dblcmp(p - maxi);
}

int betweenCmp(Point a, Point b, Point c)
{
    if (fabs(b.x - c.x) > fabs(b.y - c.y))
        return xyCmp(a.x, min(b.x, c.x), max(b.x, c.x));
    else return xyCmp(a.y, min(b.y, c.y), max(b.y, c.y));
}

bool isinPolygon(Point A)
{
    int Left = 2, Right = N + 1;
    while (Left < Right)
    {
        int Mid = (Left + Right) >> 1;
        if (dblcmp(cross_product(P[1], A, P[Mid])) <= 0) Left = Mid + 1;
        else Right = Mid;
    }
    int tmp = dblcmp(cross_product(P[Left - 1], P[Left], A));
    if (tmp > 0) return true;
    if (tmp == 0 && betweenCmp(A, P[Left - 1], P[Left]) <= 0) return true;
    return false;
}

double MiniDistance(Point p0, Point p1, Point p2)
{
	double d = Distance(p1, p2);
	double u = Dot_product(p1, p0, p2) / (d * d);
	if (u < 0)
		return Distance(p0, p1);
	else if (u > 1)
		return Distance(p0, p2);
	else
	{
		Point v;
		v.x = p1.x + u * (p2.x - p1.x);
		v.y = p1.y + u * (p2.y - p1.y);
		return Distance(p0, v);
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%lf%lf%d", &sta.x, &sta.y, &N);
	for (int i = 1; i <= N; i++)
		scanf("%lf%lf", &P[i].x, &P[i].y);
	P[N + 1] = P[1];
	if (isinPolygon(sta)) printf("0\n");
	else
	{
		double ans = 1e10;
		for (int i = 1; i <= N; i++)
		{
			double dis = MiniDistance(sta, P[i], P[i + 1]);
			if (dblcmp(dis - ans) < 0) ans = dis;
		}
		printf("%.3lf\n", 2.0 * ans);
	}
	return 0;
}
