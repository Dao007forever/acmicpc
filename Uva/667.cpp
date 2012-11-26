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

const double PI = acos(-1.0);

double Angle(double x0, double y0, double x1, double y1)
{
	double a = atan2(y0, x0);
	double b = atan2(y1, x1);
	if (b - a > PI) a += 2 * PI;
	if (a - b > PI) b += 2 * PI;
	return a - b;
}

int main()
{
	freopen("a", "r", stdin);
	int n, T;
	scanf("%d", &T);
	while (T--)
	{
		double h, k, x[101], y[101], Max = 0, Min = 0, sum = 0;
		scanf("%lf%lf%d", &k, &h, &n);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &x[i], &y[i]);
		x[n] = x[0]; y[n] =y[0];
		for (int i = 0; i < n; i++)
		{
			sum += Angle(x[i], y[i], x[i + 1], y[i + 1]);
			if (sum < Min) Min = sum;
			if (sum > Max) Max = sum;
			if (Max - Min >= 2 * PI)
			{
				Max = Min + 2 * PI;
				break;
			}
		}
		printf("%.2lf\n", (Max - Min) * k * h);
		if (T) printf("\n");
	}
	return 0;
}

