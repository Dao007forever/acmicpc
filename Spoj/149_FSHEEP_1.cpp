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

const int MAXN = 100000 + 10;
const double eps = 1e-6;
struct Point
{
	double x, y;
}P[MAXN], po[MAXN];
int N, M, K;

double dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double cross_product(Point a, Point b, Point c)
{
	return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

int xyCmp(double p, double mini, double maxi)
{
	return dblcmp(p - mini) * dblcmp(p - maxi);
}

int betweenCmp(Point a, Point b, Point c)
{
	if (fabs(b.x - c.x) > fabs(b.y - c.y))
		return xyCmp(a.x, min(b.x, c.x), max(b.x, c.x));
	else return xyCmp(a.y, min(b.y, c.y), max(b.y, c.y));
}

bool isinPolygon(Point A)
{
	int Left = 2, Right = N + 1;
	while (Left < Right)
	{
		int Mid = (Left + Right) >> 1;
		if (dblcmp(cross_product(P[1], A, P[Mid])) <= 0) Left = Mid + 1;
		else Right = Mid;
	}
	int tmp = dblcmp(cross_product(P[Left - 1], P[Left], A));
	if (tmp > 0) return true;
	if (tmp == 0 && betweenCmp(A, P[Left - 1], P[Left]) <= 0) return true;
	return false;
}

void solve()
{
	int tot = 0;
	for (int i = 1; i <= M; i++)
	{
		if (isinPolygon(po[i])) tot++;
	}
	cout << tot << endl;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
			scanf("%lf%lf", &P[i].x, &P[i].y);
		P[N + 1] = P[1];
		for (int i = 1; i <= M; i++)
		{
			scanf("%lf%lf", &po[i].x, &po[i].y);
		}
		solve();
	}
	return 0;
}
