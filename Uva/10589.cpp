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

const double eps = 1e-14;
struct Point
{
	double x, y;
	void init(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
}p[111111];
struct Circle
{
	Point center;
	double radis;
}c[5];
int N, a;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double dist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool inCircle(Point p, Circle c)
{
	double dis = dist(p, c.center);
	if (dblcmp(c.radis - dis) >= 0) return true;
	return false;
}

bool check(Point tmp)
{
	for (int i = 1; i <= 4; i++)
		if (!inCircle(tmp, c[i])) return false;
	return true;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &a) != EOF)
	{
		if (N == 0 && a == 0) break;
		c[1].center.init(0.0, 0.0);
		c[2].center.init((double)a, 0.0);
		c[3].center.init((double)a, (double)a);
		c[4].center.init(0.0, (double)a);
		for (int i = 1; i <= 4; i++)
			c[i].radis = (double)a;
		for (int i = 1; i <= N; i++)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		int cnt = 0;
		for (int i = 1; i <= N; i++)
		{
			if (check(p[i])) cnt++;
		}
		double area = (double)cnt / N * a * a;
		printf("%.5lf\n", area);
	}
	return 0;
}
