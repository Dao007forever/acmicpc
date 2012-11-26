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

const double PI = acos(-1.0);
const double eps = 1e-6;
struct Point
{
	double x, y;
}a, b, c;

double dist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double Area(int n, double radis)
{
	double ang = (2 * PI) / n;
	double ar = radis * radis * sin(ang) / 2.0;
	return ar * n;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
	double A = dist(b, c);
	double B = dist(a, c);
	double C = dist(a, b);
	double dA = acos((B * B + C * C - A * A) / 2.0 / B / C);
	double dB = acos((A * A + C * C - B * B) / 2.0 / A / C);
	double dC = acos((A * A + B * B - C * C) / 2.0 / A / B);
	
	double S = 0.5 * B * C * sin(dA);
	double radis = (A * B * C) / 4 / S;
	dA *= 2.0, dB *= 2.0, dC *= 2.0;

	for (int i = 3; i <= 100; i++)
	{
		double tmp = (2 * PI) / (double)i;
		int p1 = (int)((dA + eps) / tmp);
		int p2 = (int)((dB + eps) / tmp);
		int p3 = (int)((dC + eps) / tmp);
		if (p1 + p2 + p3 == i)
		{
			printf("%.8lf\n", Area(i, radis));
			return 0;
		}
	}
	return 0;
}
