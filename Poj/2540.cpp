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

const double eps = 1e-10;
int size;
double dir;
struct Point
{
	double x, y;
}p[66], q[66];


int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

void init()
{
	size = 4;
	p[1].x = p[1].y = 0.0;
	p[2].x = 10.0, p[2].y = 0.0;
	p[3].x = p[3].y = 10.0;
	p[4].x = 0.0, p[4].y = 10.0;
	p[0] = p[4];
	p[5] = p[1];
}

Point SegCross(Point p1, Point p2, double a, double b, double c)
{
	Point tmp;
	double u = fabs(a * p1.x + b * p1.y + c);
	double v = fabs(a * p2.x + b * p2.y + c);
	tmp.x = (p1.x * v + p2.x * u) / (u + v);
	tmp.y = (p1.y * v + p2.y * u) / (u + v);
	return tmp;
}

void HulfPlaneCut(double a, double b, double c)
{
	int s = 0;
	for (int i = 1; i <= size; i++)
	{
		if (dblcmp((a * p[i].x + b * p[i].y +c) * dir) >= 0)
			q[++s] = p[i];
		else
		{
			if (dblcmp((a * p[i - 1].x + b * p[i - 1].y + c) * dir) > 0)
				q[++s] = SegCross(p[i - 1], p[i], a, b, c);
			if (dblcmp((a * p[i + 1].x + b * p[i + 1].y + c) * dir) > 0)
				q[++s] = SegCross(p[i], p[i + 1], a, b, c);
		}
	}
	for (int i = 1; i <= s; i++)
		p[i] = q[i];
	p[s + 1] = p[1];
	p[0] = p[s];
	size = s;
}

void solve(Point p0, Point t1, Point t2)
{
	double a = t2.y - t1.y, b = t1.x - t2.x, c = t2.x * t1.y - t2.y * t1.x;
	dir = a * p0.x + b * p0.y + c;
	HulfPlaneCut(a, b, c);
}

double Get_area()
{
	double area = 0.0;
	for (int i = 1; i <= size; i++)
		area += p[i].x * p[i + 1].y - p[i].y * p[i + 1].x;
	return fabs(area / 2);
}

int main()
{
	freopen("a", "r", stdin);
	Point p1, p2, t1, t2;
	p1.x = 0.0, p1.y = 0.0;
	bool flag = true;
	init();
	char op[10];
	while (scanf("%lf%lf%s", &p2.x, &p2.y, op) != EOF)
	{
		t1.x = (p1.x + p2.x) / 2;
		t1.y = (p1.y + p2.y) / 2;
		t2.x = t1.x + p1.y - p2.y;
		t2.y = t1.y + p2.x - p1.x;
		if (strcmp("Same", op) == 0 || !flag)
		{
			flag = false;
			printf("0.00\n");
			continue;
		}
		if (strcmp("Colder", op) == 0)
		{
			solve(p1, t1, t2);
		}
		else if (strcmp("Hotter", op) == 0)
		{
			solve(p2, t1, t2);
		}
		double area = Get_area();
		printf("%.2lf\n", area);
		if (fabs(area) == 0) flag = false;
		p1 = p2;
	}
	return 0;
}
