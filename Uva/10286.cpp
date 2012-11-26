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

double ang(double a)
{
	return a * PI / 180;
}

int main()
{
	freopen("a", "r", stdin);
	double x;
	while (scanf("%lf", &x) != EOF)
	{
		double ans = x * sin(ang(108)) / sin(ang(63));
		printf("%.10lf\n", ans);
	}
	return 0;
}
