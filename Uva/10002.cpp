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

const int MAXN = 111;
const double eps = 1e-6;
struct Point
{
	double x, y;
}P[MAXN];
int N, top;
Point Stack[MAXN];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double cross_product(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Point Bary_Center(Point p[], int n)
{
	Point ans, t;
	double area = 0.0, tmp;
	ans.x = ans.y = 0.0;
	for (int i = 1; i < n - 1; i++)
	{
		tmp = cross_product(p[i], p[0], p[i + 1]) / 2.0;
		ans.x += (p[0].x + p[i].x + p[i + 1].x) * tmp;
		ans.y += (p[0].y + p[i].y + p[i + 1].y) * tmp;
		area += tmp;
	}
	ans.x /= (3 * area);
	ans.y /= (3 * area);
	return ans;
}

bool cmp(Point a, Point b)
{
    return cross_product(P[0], a, b) < eps;
}

void Graham(int n)
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
                while (dblcmp(cross_product(Stack[top], Stack[top - 1], P[i])) < 0 && top >= 1)
                        top--;
                Stack[++top] = P[i];
        }

		Point res = Bary_Center(Stack, top + 1);
		printf("%.3lf %.3lf\n", res.x, res.y);
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N >= 3)
	{
		for (int i = 0; i < N; i++)
			scanf("%lf%lf", &P[i].x, &P[i].y);
		Graham(N);
	}
	return 0;
}
