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

const double eps = 1e-6;
int N;
double x[15], y[15], r[15];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double dist(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool Check(double xx, double yy)
{
	for (int i = 1; i <= N; i++)
	{
		if (dblcmp(dist(xx, yy, x[i], y[i]) - r[i]) <= 0)
			return true;
	}
	return false;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%lf%lf%lf", &x[i], &y[i], &r[i]);
		x[i] *= 100; y[i] *= 100; r[i] *= 100;
	}

	int ans = 0;
	for (int i = 1; i <= 100; i++)
	for (int j = 1; j <= 100; j++)
	if (Check(i, j)) ans++;
	printf("%.0lf\n", (double)ans / 100);
	return 0;
}
