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

const int MAXN = 3000 + 10;
const double eps = 1e-8;
struct Point
{
	double x, y;
}p[MAXN * 10];
struct Line
{
	Point a, b;
}l[MAXN];
int n, cnt;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double Cross(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Point SegCross(Point a, Point b, Point c, Point d)
{
	Point temp;
	double s1 = Cross(a, b, c), s2 = Cross(a, b, d);
	temp.x = (c.x * s2 - d.x * s1) / (s2 - s1);
	temp.y = (c.y * s2 - d.y * s1) / (s2 - s1);
	return temp;
}

bool compare(Point a, Point b)
{
	return dblcmp(a.x - b.x) == 0 && dblcmp(a.y - b.y) == 0;
}

int FindDiff()
{
	int num = 1;
	Point now = p[0];
	for (int i = 1; i < cnt; i++)
		if (!compare(now, p[i]))
		{
			now = p[i];
			num++;
		}
	return num;
}

bool cmp(const Point &a, const Point &b)
{
	if (dblcmp(a.x - b.x) == 0) return dblcmp(a.y - b.y) < 0;
	return dblcmp(a.x - b.x) < 0;
}

bool parallel(Point a, Point b, Point c, Point d)
{
	return dblcmp((a.x - b.x) * (c.y - d.y) - (c.x - d.x) * (a.y - b.y)) == 0;
}

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 1; i <= n; i++)
			scanf("%lf%lf%lf%lf", &l[i].a.x, &l[i].a.y, &l[i].b.x, &l[i].b.y);
		int ret = 2;
		for (int i = 2; i <= n; i++)
		{
			cnt = 0;
			for (int j = 1; j < i; j++)
			{
				if (parallel(l[i].a, l[i].b, l[j].a, l[j].b)) continue;
				Point tmp = SegCross(l[i].a, l[i].b, l[j].a, l[j].b);
				p[cnt++] = tmp;
			}
			sort(p, p + cnt, cmp);
			int inc = FindDiff();
			ret += inc + 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
