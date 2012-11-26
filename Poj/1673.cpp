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

const double eps = 1e-6;
int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}
struct Point
{
	double x, y;
	void set(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	void output()
	{
		if (dblcmp(x) == 0) x = 0.0;
		if (dblcmp(y) == 0) y = 0.0;
		printf("%.4f %.4f\n", x, y);
	}
};

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

Point a, b, c, res, bc, ac, ah, bh;
int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
		bc.set(c.x - b.x, c.y - b.y);
		ac.set(c.x - a.x, c.y - a.y);
		ah.set(-bc.y, bc.x);
		bh.set(-ac.y, ac.x);
		ah.set(a.x + ah.x, a.y + ah.y);
		bh.set(b.x + bh.x, b.y + bh.y);
		res = SegCross(a, ah, b, bh);
		res.output();
	}
	return 0;
}
