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
int n, top;
Point Stack[MAXN];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double cross_product(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(Point a, Point b)
{
	return cross_product(P[0], a, b) < eps;
}

double dist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
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
}
int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &n) && n)
	{
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &P[i].x, &P[i].y);
		Graham(n);
		Stack[top + 1] = Stack[0];
		double ans = 0.0;
		if (n == 1)
		{
			printf("0.00\n");
			continue;
		}
		if (n == 2)
		{
			ans = dist(P[0], P[1]);
			printf("%.2lf\n", 2 * ans);
			continue;
		}
		for (int i = 0; i <= top; i++)
			ans += dist(Stack[i], Stack[i + 1]);
		printf("%.2lf\n", ans);
	}
	return 0;
}
