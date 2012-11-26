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
const double eps = 1e-6;
struct Point
{
	double x, y;
	void set(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	double dist()
	{
		return sqrt(x * x + y * y);
	}
};
struct Seg
{
	Point p1, p2;
}seg[MAXN];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

int N;
Point Light;
Point center;
double radis;

double dist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

//将向量p逆时针旋转angle角度
Point Rotate(Point p, double angle)
{
	Point res;
	res.x = p.x * cos(angle) - p.y * sin(angle);
	res.y = p.x * sin(angle) + p.y * cos(angle);
	return res;
}

void TangentPoint(Point poi, Point o, double radis, Point &res1, Point &res2)
{
	double line = dist(poi, o);
	double angle = acos(radis / line);
	Point temp, lin;//temp为圆心与poi点的连线与圆的交点
	lin.x = poi.x - o.x;
	lin.y = poi.y - o.y;
	temp.x = lin.x / lin.dist() * radis;
	temp.y = lin.y / lin.dist() * radis;
	res1 = Rotate(temp, -angle);
	res2 = Rotate(temp, angle);
	res1.x += o.x, res1.y += o.y;
	res2.x += o.x, res2.y += o.y;
}

double Cross(Point a, Point b, Point c)
{
	return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

Point SegCross(Point a, Point b, Point c, Point d)
{
	Point temp;
	double s1 = Cross(a, b, c), s2 = Cross(a, b, d);
	temp.x = (c.x * s2 - d.x * s1) / (s2 - s1);
	temp.y = (c.y * s2 - d.y * s1) / (s2 - s1);
	return temp;
}

void swap(Point &a, Point &b)
{
	Point temp = a;
	a = b;
	b = temp;
}

void solve(int idx)
{
	Point inter1, inter2;//两个公切点
	TangentPoint(Light, center, radis, inter1, inter2);
	Point infa, infb;
	infa.x = -1e10, infa.y = 0.0;
	infb.x = 1e10, infb.y = 0.0;
	seg[idx].p1 = SegCross(infa, infb, inter1, Light);
	seg[idx].p2 = SegCross(infa, infb, inter2, Light);
	if (dblcmp(seg[idx].p1.x - seg[idx].p2.x) > 0)
		swap(seg[idx].p1, seg[idx].p2);
}

bool cmp(Seg a, Seg b)
{
	if (dblcmp(a.p1.x - b.p1.x) == 0) 
		return dblcmp(a.p2.x - b.p2.x) < 0;
	return dblcmp(a.p1.x - b.p1.x) < 0;
}

int main()
{
	freopen("a", "r", stdin);
	int N;
	while (scanf("%d", &N) && N)
	{
		scanf("%lf%lf", &Light.x, &Light.y);
		for (int i = 0; i < N; i++)
		{
			scanf("%lf%lf%lf", &center.x, &center.y, &radis);
			solve(i);
		}
		sort(seg, seg + N, cmp);

		/*for (int i = 0; i < N; i++)
		{
			printf("%.2lf %.2lf\n", seg[i].p1.x, seg[i].p2.x);
		}*/

		printf("%.2lf", seg[0].p1.x);
		double pre = seg[0].p2.x;
		for (int i = 1; i < N; i++)
		{
			if (dblcmp(seg[i].p1.x > pre))
			{
				printf(" %.2lf\n%.2lf", pre, seg[i].p1.x);
			}
			if (pre < seg[i].p2.x) pre = seg[i].p2.x;
		}
		printf(" %.2lf\n", pre);
		printf("\n");
	}
	return 0;
}
