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

const double eps = 1e-8;
double x, y, c;

double Cal(double d)
{
	return 1 / sqrt(x * x - d * d) + 1 / sqrt(y * y - d * d);
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%lf%lf%lf", &x, &y, &c) != EOF)
	{
		c = 1 / c;
		double Left = 0, Right = min(x, y);
		while (Left < Right - eps)
		{
			double Mid = (Left + Right) / 2.0;
			if (Cal(Mid) > c) Right = Mid;
			else Left = Mid;
		}
		printf("%.3lf\n", Right);
	}
	return 0;
}
