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

#define maxn 110

const double eps = 1e-8;
int sig(double d)
{
	return (d > eps) - (d < -eps);
}
struct Point
{
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	Point operator + (Point p)
	{
		return Point(x + p.x, y + p.y);
	}
	Point operator - (Point p)
	{
		return Point(x - p.x, y - p.y);
	}
	Point operator * (double d)
	{
		return Point(x * d, y * d);
	}
	bool operator < (const Point &p) const
	{
		return sig(x - p.x) != 0 ? x < p.x : sig(y - p.y) < 0;
	}
	Point resize(double d)
	{
		d /= sqrt(x * x + y * y);
		return Point(x * d, y * d);
	}
	void input()
	{
		scanf("%lf%lf", &x, &y);
	}
};
double dis(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double dot(Point o, Point a, Point b)
{
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
double cross(Point o, Point a, Point b)
{
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
bool onSeg(Point p, Point a, Point b)
{
	return sig(cross(p, a, b)) == 0 && sig(dot(p, a, b)) <= 0;
}
int inPolygon(Point *ps, int n, Point p)
{
	int cnt = 0;
	ps[n] = ps[0];
	for (int i = 0; i < n; i++)
	{
		if (onSeg(p, ps[i], ps[i + 1])) return 2;
		int k = sig(cross(ps[i], ps[i + 1], p));
		int d1 = sig(ps[i + 0].y - p.y);
		int d2 = sig(ps[i + 1].y - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0) cnt++;
		if (k < 0 && d2 <= 0 && d1 > 0) cnt--;
	}
	return cnt != 0;
}
int btw(Point x, Point a, Point b)
{
	return sig(dot(x, a, b));
}
int segCross(Point a, Point b, Point c, Point d, Point &p)
{
	double s1, s2;
	int d1, d2, d3, d4;
	d1 = sig(s1 = cross(a, b, c));
	d2 = sig(s2 = cross(a, b, d));
	d3 = sig(cross(c, d, a));
	d4 = sig(cross(c, d, b));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
	{
		p.x = (c.x * s2 - d.x * s1) / (s2 - s1);
		p.y = (c.y * s2 - d.y * s1) / (s2 - s1);
		return 1;
	}
	if (d1 == 0 && btw(c, a, b) <= 0 ||
		d2 == 0 && btw(d, a, b) <= 0 ||
		d3 == 0 && btw(a, c, d) <= 0 ||
		d4 == 0 && btw(b, c, d) <= 0)
		return 2;
	return 0;
}
//whether segment ab is in ps?
bool inPolygon(Point *ps, int n, Point a, Point b)
{
	int valA = inPolygon(ps, n, a);
	int valB = inPolygon(ps, n, b);
	if (valA == 0 || valB == 0) return false;

	static Point arr[maxn + 10];
	int len = 0;
	if (valA == 2) arr[len++] = a;
	if (valB == 2) arr[len++] = b;

	ps[n] = ps[0];
	for (int i = 0; i < n; i++)
	{
		if (onSeg(ps[i], a, b))
		{
			arr[len++] = ps[i];
		}
		else
		{
			Point tmp;
			if (1 == segCross(ps[i], ps[i + 1], a, b, tmp))
				return false;
		}
	}
	sort(arr, arr + len);
	for (int i = 0; i < len - 1; i++)
		if (0 == inPolygon(ps, n, (arr[i] + arr[i + 1]) * 0.5))
			return false;
	return true;
}
double test(Point *ps, int n, Point a, Point b)
{
	Point vec = (b - a).resize(1);
	double l = 0, r = 1e6;
	while (r - l > 1e-6)
	{
		double m = (l + r) / 2;
		if (inPolygon(ps, n, a, b + vec * m))
		{
			l = m;
		}
		else
		{
			r = m;
		}
	}
	return (l + r) / 2;
}
//assume: ps is anti-clockwise !!!!!!!!!!!!!!!!!
double maxDisInPolygon(Point *ps, int n)
{
	ps[n] = ps[0];
	double ans = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (!inPolygon(ps, n, ps[i], ps[j]))
			{
				continue;
			}
			ans = max(ans, test(ps, n, ps[i], ps[j]) + test(ps, n, ps[j], ps[i]) + dis(ps[i], ps[j]));
		}
	}
	return ans;
}
int graham(Point *p, int n, int *ch)
{
	sort(p, p + n);
	int len = 0, len0 = 1, i;
	for (i = 0; i < n; i++)
	{
		while (len > len0 && sig(cross(p[ch[len - 1]], p[ch[len - 2]], p[i])) <= 0)
			len--;
		ch[len++] = i;
	}
	len0 = len;
	for (i = n - 2; i >= 0; i--)
	{
		while (len > len0 && sig(cross(p[ch[len - 1]], p[ch[len - 2]], p[i])) <= 0)
			len--;
		ch[len++] = i;
	}
	return len - 1;
}
double minDisOfConvex(Point *ps, int n)
{
	static int ch[maxn];
	int len = graham(ps, n, ch);
	double ans = 1e30;
	for (int i = 0; i < len; i++)
	{
		double tmp = -1;
		double segLen = dis(ps[ch[i]], ps[ch[i + 1]]);
		for (int j = 0; j < len; j++)
		{
			tmp = max(tmp, fabs(cross(ps[ch[j]], ps[ch[i]], ps[ch[i + 1]]) / segLen));
		}
		ans = min(ans, tmp);
	}
	return ans;
}

Point hole[maxn], coin[maxn];
int holeN, coinN;

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d", &holeN);
		for (int i = 0; i < holeN; i++)
		{
			hole[i].input();
		}
		scanf("%d", &coinN);
		for (int i = 0; i < coinN; i++)
		{
			coin[i].input();
		}
		double maxDisHole = maxDisInPolygon(hole, holeN);
		double minDisCoin = minDisOfConvex(coin, coinN);

		if (sig(maxDisHole - minDisCoin) >= 0)
		{
			printf("legal\n");
		}
		else
		{
			printf("illegal\n");
		}
	}
	return 0;
}
