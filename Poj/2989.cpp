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
#define sqr(v) ((v) * (v))
const int MAXN = 60;
const double PI = acos(-1.0);
const double eps = 1e-8;
double my_acos(double d)
{
        return acos(d > 1 ? 1 : d < -1 ? -1 : d);
}
double my_sqrt(double d)
{
        return sqrt(max(d, 0.0));
}
int dblcmp(double d)
{
        return (d > eps) - (d < -eps);
}
struct Point 
{
        double x, y;
        Point(){}
        Point(double x, double y) : x(x), y(y) {}
        Point resize(double d)
        {
                d /= my_sqrt(x * x + y * y);
                return Point(x * d, y * d);
        }
        Point left90()
        {
                return Point(-y, x);
        }
        Point operator-(const Point & o) const
        {
                return Point(this->x - o.x, this->y - o.y);
        }
        Point operator+(const Point & o) const
        {
                return Point(this->x + o.x, this->y + o.y);
        }
        Point operator*(double d)
        {
                return Point(x * d, y * d);
        }
        void output()
        {
                printf("x = %.2f, y = %.2f\n", x, y);
        }
};
double cross(Point o, Point a, Point b)
{
        return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
double dot(Point o, Point a, Point b)
{
        return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
double dis(Point a, Point b)
{
        return my_sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
int btw(Point o, Point a, Point b)
{
        return dblcmp(dot(o, a, b));
}
struct Circle
{
        Point center;
        double radis;
};


//返回点o到直线ab的距离，res保存o在ab上的投影

double pointToLine(Point o, Point a, Point b, Point & res)
{
        double d = dis(a, b);
        double s = cross(a, b, o) / d;
        res = o + (a - b).left90() * (s / d);
        return fabs(s);
}

//判断直线与圆相交
//1相交，0相切，-1不相交
int intersect(Point a, Point b, Circle c, Point &p1, Point &p2)
{
        Point p;
        double d = pointToLine(c.center, a, b, p);
        int v = dblcmp(c.radis - d);
        if (v != -1)
        {
                Point vec = (b - a).resize(my_sqrt(sqr(c.radis) - sqr(d)));
                p1 = p + vec;
                p2 = p - vec;
        }
        return v;
}

//返回圆c和三角形oab相交的有向面积
double intersectArea(Circle c, Point a, Point b)
{
        if (dblcmp(cross(c.center, a, b)) == 0) return 0.0;//共线，三角形退化

        Point o = c.center, p[5];
        double r = c.radis;
        int len = 0;

        p[len++] = a;
        if (intersect(a, b, c, p[1], p[2]) == 1)//正交
        {
                if (btw(p[1], a, b) < 0) p[len++] = p[1];
                if (btw(p[2], a, b) < 0) p[len++] = p[2];
        }
        p[len++] = b;
        if (len == 4 & btw(p[1], p[0], p[2]) > 0) swap(p[1], p[2]);

        double res = 0;
        for (int i = 0; i < len - 1; i++)
        {
                if (dblcmp(dis(o, p[i]) - r) > 0 || dblcmp(dis(o, p[i + 1]) - r) > 0)//外部！扇形
                {
                        double theta = my_acos(dot(o, p[i], p[i + 1]) / dis(o, p[i]) / dis(o, p[i + 1]));
                        res += theta * r * r / 2.0;
                }
                else //内部！三角形
                {
                        res += fabs(cross(o, p[i], p[i + 1]) / 2.0);
                }
        }
        if (dblcmp(cross(o, a, b)) < 0) res = -res;//有向面积
        return res;
}

//返回圆c与多边形ps相交面积（ps为任意简单多边形）
double intersectArea(Circle c, Point * ps, int n)
{
        ps[n] = ps[0];
        double res = 0;
        for (int i = 0; i < n; i++)
        {
                res += intersectArea(c, ps[i], ps[i + 1]);
        }
        return fabs(res);
}

//poj-2989	求圆与三角形的面积交
Point ps[5];
int main()
{
	freopen("a", "r", stdin);
	Circle c;
	double x, y, r;
	while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf", &ps[0].x, &ps[0].y, &ps[1].x, &ps[1].y, &ps[2].x, &ps[2].y, &x, &y, &r) != EOF)
	{
		c.center = Point(x, y);
		c.radis = r;
		printf("%.2f\n", intersectArea(c, ps, 3));
	}
	return 0;
}
