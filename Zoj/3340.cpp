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
struct Point
{
	int x, y, z;
}P[MAXN], line[2];
int N;

double dis(Point a, Point b)
{
	double dx = (double)(a.x - b.x);
	double dy = (double)(a.y - b.y);
	double dz = (double)(a.z - b.z);
	return sqrt(dx * dx + dy * dy + dz * dz);
}

bool check(double a, double b, double c)
{
	double t = a;
	if (b > t) t = b;
	if (c > t) t = b;
	
	if (t == a) return b * b + c * c > a * a;
	if (t == b) return a * a + c * c > b * b;
	if (t == c) return a * a + b * b > c * c;
//	return a * a + b * b < c * c;
}

void solve()
{
	double ans = 0;
	for (int i = 1; i <= N; i++)
	{
		double a = dis(line[0], P[i]), b = dis(line[0], line[1]), c = dis(line[1], P[i]);
		double p = 0.5 * (a + b + c);
		double S = sqrt(p * (p - a) * (p - b) * (p - c));
		double now = min(a, c);
		if (check(a, b, c)) now = min(now, S * 2 / b);
		ans = max(ans, now);
	}
	printf("%.2lf\n", ans);
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) != EOF)
	{
		scanf("%d%d%d", &line[0].x, &line[0].y, &line[0].z);
		scanf("%d%d%d", &line[1].x, &line[1].y, &line[1].z);
		for (int i = 1; i <= N; i++)
			scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].z);

		solve();
	}
}
