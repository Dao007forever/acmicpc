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

double x, y, z;

double cal(double a, double b, double c)
{
	double p = (a + b + c) / 2.0;
	double ans = sqrt(p * (p - a) * (p - b) * (p - c));
	return ans;
}

bool check(double a, double b, double c)
{
	if (a >= b + c || a <= fabs(b - c)) return true;
	return false;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%lf%lf%lf", &x, &y, &z) != EOF)
	{
		if (check(x, y, z) || check(y, z, x) || check(z, x, y))
		{
			printf("-1.000\n");
			continue;
		}
		double area = 4.0 / 3 * cal(x, y, z);
		if (area <= 0)
		{
			printf("-1.000\n");
			continue;
		}
		printf("%.3lf\n", area);
	}
	return 0;
}
