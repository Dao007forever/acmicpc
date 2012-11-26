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

const int MAXN = 155;
const double pi = acos(-1);
const double eps = 1e-8;
struct Point
{
	double x , y , k ;
	void Init( double a , double b )
	{
		x = a ;
		y = b ;
	}
	Point operator + ( Point P )
	{
		Point Ret ;
		Ret.x = x + P.x ;
		Ret.y = y + P.y ;
		return Ret ;
	}
	Point operator - ( Point P )
	{
		Point Ret ;
		Ret.x = x - P.x ;
		Ret.y = y - P.y ;
		return Ret ;
	}
	Point Rotate( double theta )
	{
		Point T;
		T.x = x * cos( theta ) + y * sin( theta ) ;
		T.y = y * cos( theta ) - x * sin( theta ) ;
		return T;
	}
	double Length()
	{
		return sqrt( x * x + y * y ) ;
	}
}a[MAXN];
int n, m1, m2;
double d;

double dis(Point A, Point B)
{
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

bool Get(Point Mid)
{
	Point XL, tmp;
	XL.x = a[m1].x - Mid.x;
	XL.y = a[m1].y - Mid.y;
	double tt = 2 * pi / n;
	tmp = XL.Rotate(tt * (m2 - m1));
	tmp.x += Mid.x;
	tmp.y += Mid.y;
	if  (fabs(tmp.x - a[m2].x) < eps && fabs(tmp.y - a[m2].y) < eps)
	{
		int i, j = 0;
		for (i = m1 % n + 1; i != m1; i = i % n + 1)
		{
			j++;
			tmp = XL.Rotate(tt * j);
			a[i].x = tmp.x + Mid.x;
			a[i].y = tmp.y + Mid.y;
		}
		for (i = 1; i <= n; i++)
			printf("%.6lf %.6lf\n", a[i].x, a[i].y);
		return true;
	}
	else return false;
}

bool Try()
{
	Point tmp, Mid;
	Mid.x = (a[m1].x + a[m2].x) / 2;
	Mid.y = (a[m1].y + a[m2].y) / 2;
	if ((m2 - m1) * 2 == n) return Get(Mid);
	Point XL;
	double k;
	XL.x = a[m2].x - a[m1].x;
	XL.y = a[m2].y - a[m1].y;
	tmp = XL.Rotate(pi / 2);
	k = sqrt(d * d / (tmp.x * tmp.x + tmp.y * tmp.y));
	tmp.x *= k;
	tmp.y *= k;
	tmp.x += Mid.x;
	tmp.y += Mid.y;
	if (Get(tmp)) return true;
	tmp.x -= Mid.x;
	tmp.y -= Mid.y;
	tmp = tmp.Rotate(pi);
	tmp.x += Mid.x;
	tmp.y += Mid.y;
	Get(tmp);
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d%d", &n, &m1, &m2);
	scanf("%lf%lf%lf%lf", &a[m1].x, &a[m1].y, &a[m2].x, &a[m2].y);
	if (m1 > m2) swap(m1, m2);
	double angle = pi / n * (m2 - m1);
	while (angle > pi)
		angle -= pi;
	while (angle < -pi)
		angle += pi;
	if ((m2 - m1) * 2 == n) Try();
	else
	{
		d = dis(a[m1], a[m2]) / 2 / tan(angle);
		Try();
	}
	return 0;
}
