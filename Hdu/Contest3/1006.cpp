#include <map>
#include <set>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 55555;
const double eps = 1e-8;
struct Point
{
	double x, y;
}P[MAXN], center;
int n, top, buttom;
Point Stack[MAXN];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double cross(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline double sqr(double x)
{
	return x * x;
}

inline double dist(Point a, Point b)
{
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

bool cmp(Point a, Point b)
{
    return dblcmp(cross(P[0], a, b)) < 0;
}

void Graham()
{
        int tmp = 0;
        for (int i = 1; i < n; i++)
        if (dblcmp(P[i].x - P[tmp].x) < 0 || (dblcmp(P[i].x - P[tmp].x) == 0 && dblcmp(P[i].y - P[tmp].y) < 0))
                tmp = i;
        swap(P[0], P[tmp]);
        sort(P + 1, P + n, cmp);
        Stack[0] = P[0]; Stack[1] = P[1];
        top = 1;
        for (int i = 2; i < n; i++)
        {
                while (dblcmp(cross(Stack[top], Stack[top - 1], P[i])) < 0 && top >= 1)
                        top--;
                Stack[++top] = P[i];
        }
}

Point Bary_Center()
{
	Point ans, t;
	t.x = t.y = 0.0;
	double area = 0.0, tmp;
	ans.x = ans.y = 0.0;
	for (int i = 0; i < n - 1; i++)
	{
		tmp = cross(t, P[i], P[i + 1]);
		ans.x += (P[i].x + P[i + 1].x) * tmp;
		ans.y += (P[i].y + P[i + 1].y) * tmp;
		area += tmp;
	}
	tmp = cross(t, P[n - 1], P[0]);
	ans.x += (P[n - 1].x + P[0].x) * tmp;
	ans.y += (P[n - 1].y + P[0].y) * tmp;
	area += tmp;
	ans.x /= (3 * area);
	ans.y /= (3 * area);
	return ans;
}

bool check(Point a, Point b, Point cen)
{
	double x1 = cen.x - a.x, y1 = cen.y - a.y;
	double x2 = b.x - a.x, y2 = b.y - a.y;
	double s1 = x1 * x2 + y1 * y2;
	x1 = cen.x - b.x, y1 = cen.y -b.y;
	x2 = a.x - b.x, y2 = a.y - b.y;
	double s2 = x1 * x2 + y1 * y2;
	if (dblcmp(s1) > 0 && dblcmp(s2) > 0) return true;
	return false;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &P[i].x, &P[i].y);
		center = Bary_Center();
		Graham();
		Stack[++top] = Stack[0];
		int ans = 0;
		for (int i = 0; i < top; i++)
		{
			if (check(Stack[i], Stack[i + 1], center)) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
