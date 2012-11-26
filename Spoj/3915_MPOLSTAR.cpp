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

const int MAXN = 55;
const double eps = 1e-8;
double sqr(double d)
{
	return d * d;
}
int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}
struct Point
{
    double x, y;
    Point(double x, double y) : x(x), y(y){}
    Point() {}
    Point operator - (const Point &p) const
    {
        return Point(x - p.x, y - p.y);
    }
    Point operator + (const Point &p) const
    {
        return Point(x + p.x, y + p.y);
    }
    bool operator == (const Point &p) const
    {
        return dblcmp(x - p.x) == 0 && dblcmp(y - p.y) == 0;
    }
    Point resize(double d)
    {
        d /= sqrt(sqr(x) + sqr(y));
        return Point(x * d, y * d);
    }
    Point left90()
    {
        return Point(-y, x);
    }
	void input()
	{
		scanf("%lf%lf", &x, &y);
	}
};
double cross(Point o, Point a, Point b)
{
    return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

int lineCross(Point a, Point b, Point c, Point d, Point &p)
{
    double s1, s2;
    s1 = cross(a, b, c);
    s2 = cross(a, b, d);
    if (dblcmp(s1) == 0 && dblcmp(s2) == 0) return 2;
    if (dblcmp(s2 - s1) == 0) return 0;
    p.x = (c.x * s2 - d.x * s1) / (s2 - s1);
    p.y = (c.y * s2 - d.y * s1) / (s2 - s1);
    return 1;
}

//多边形切割
//用直线ab切割多边形p，切割后的在向量(a,b)的左侧，并原地保存切割结果
//如果退化为一个点，也会返回去
void polygon_cut(Point *p, int &n, Point a, Point b)
{
    static Point pp[MAXN];
    int m = 0;
    p[n] = p[0];
    for (int i = 0; i < n; i++)
    {
        if (dblcmp(cross(a, b, p[i])) > 0)
            pp[m++] = p[i];
        if (dblcmp(cross(a, b, p[i])) != dblcmp(cross(a, b, p[i + 1])))
            lineCross(a, b, p[i], p[i + 1], pp[m++]);
    }
    n = 0;
    for (int i = 0; i < m; i++)
        if (!i || !(pp[i] == pp[i - 1]))
            p[n++] = pp[i];
    while (n > 1 && p[n - 1] == p[0]) n--;
}

Point ps[MAXN], p[MAXN];
int N;

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		for (int i = 0; i < N; i++)
			ps[i].input();
		ps[N] = ps[0];
		int nn = 4;
		p[0] = Point(0, 0);
		p[1] = Point(0, 10000);
		p[2] = Point(10000, 10000);
		p[3] = Point(10000, 0);

		for (int i = 0; i < N && nn; i++)
		{
			polygon_cut(p, nn, ps[i], ps[i + 1]);
		}

		if (nn) printf("1\n");
		else printf("0\n");
	}
	return 0;
}
