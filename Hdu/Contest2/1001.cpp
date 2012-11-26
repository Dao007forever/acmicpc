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

const int MAXN = 22222;
#define sqr(v) ((v) * (v))
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
		bool operator == (const Point &p) const
		{
			return dblcmp(x - p.x) == 0 && dblcmp(y - p.y) == 0;
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

int main()
{
	freopen("b", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++)
	{
		printf("Case %d: ", cas);
		Point ps[MAXN][2], p[MAXN], origin;
		Circle circle;
		circle.center.x = 0.0, circle.center.y = 0.0;
		int n;
		scanf("%lf%d", &circle.radis, &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%lf%lf%lf%lf", &ps[i][0].x, &ps[i][0].y, &ps[i][1].x, &ps[i][1].y);
		}
		scanf("%lf%lf", &origin.x, &origin.y);
		
		int nn = 4;
		p[0] = Point(-10000.0, -10000.0);
		p[1] = Point(-10000.0, 10000.0);
		p[2] = Point(10000.0, 10000.0);
		p[3] = Point(10000.0, -10000.0);

		for (int i = 1; i <= n; i++)
		{
			if (dblcmp(cross(ps[i][0], ps[i][1], origin)) > 0)
				polygon_cut(p, nn, ps[i][0], ps[i][1]);
			else polygon_cut(p, nn, ps[i][1], ps[i][0]);
		}
		double ans = intersectArea(circle, p, nn);
		ans = ans * 100.0 / (PI * circle.radis * circle.radis);
		printf("%.5lf", ans);
		cout << "%" << endl;
	}
	return 0;
}
