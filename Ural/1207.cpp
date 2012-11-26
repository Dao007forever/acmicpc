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

const int MAXN = 10000 + 10;
const double eps = 1e-6;
struct Point
{
	double x, y;
	int id;
}P[MAXN];
int N;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double cross_product(Point a, Point b, Point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

bool cmp(Point a, Point b)
{
	return cross_product(P[0], a, b) < eps;
}
/*bool cmp(Point a, Point b)
{
	double x0 = a.x - P[0].x, y0 = a.y - P[0].y;
	double x1 = b.x - P[0].x, y1 = b.y - P[1].y;
	double k1 = atan2(y0, x0), k2 = atan2(y1, x1);
	return dblcmp(k1 - k2) < 0;
}*/

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%lf%lf", &P[i].x, &P[i].y);
		P[i].id = i + 1;
	}
	int t = 0;
	for (int i = 1; i < N; i++)
		if (P[i].x < P[t].x || (P[i].x == P[t].x && P[i].y < P[t].y))
			t = i;

	swap(P[t], P[0]);
	sort(P + 1, P + N, cmp);
	printf("%d %d\n", P[0].id, P[N / 2].id);
	return 0;
}
