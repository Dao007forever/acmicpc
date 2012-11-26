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

const double eps = 1e-8;
const double PI = acos(-1.0);
struct Point
{
	double x, y;
};
struct Circle
{
	Point c;
	double r;
}cir[22];
int N;
Point center;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double InterArea(Point p1, double r1, Point p2, double r2)
{
	double ans = 0;
	double d = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	if (r1 < r2)
	{
		swap(r1, r2);
	}
	if (dblcmp(d - r1 - r2) >= 0) return 0;
	if (dblcmp(d - r1 + r2) <= 0) return PI * r2 * r2;
	double ang1 = acos((r1 * r1 + d * d - r2 * r2) / 2.0 / r1 / d);
	double ang2 = acos((r2 * r2 + d * d - r1 * r1) / 2.0 / r2 / d);
	ans -= d * r1 * sin(ang1);
	ans += ang1 * r1 * r1 + ang2 * r2 * r2;
	return ans;
}

bool cover(int idx, double radis)
{
	double area = 0.5 * PI * cir[idx].r * cir[idx].r;
	if (dblcmp(InterArea(center, radis, cir[idx].c, cir[idx].r) - area) >= 0) return true;
	return false;
}

bool check(double radis)
{
	for (int i = 1; i <= N; i++)
	{
		center.x = cir[i].c.x, center.y = cir[i].c.y;
		bool flag = true;
		for (int i = 1; i <= N; i++)
			if (!cover(i, radis))
			{
				flag = false;
				break;
			}
		if (flag) return true;
	}
	return false;
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%lf%lf%lf", &cir[i].c.x, &cir[i].c.y, &cir[i].r);

		double Left = 0.0, Right = 100000000.0;
		double ans;
		while (Left < Right - eps)
		{
			double Mid = (Left + Right) / 2.0;
			if (check(Mid))
			{
				ans = Mid;
				Right = Mid;
			}
			else Left = Mid;
		}
		printf("%.4lf\n", ans);
	}
	return 0;
}
