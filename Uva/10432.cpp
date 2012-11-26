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
int main()
{
	freopen("a", "r", stdin);
	double radis;
	int n;
	while (scanf("%lf%d", &radis, &n) != EOF)
	{
		double ang = 2 * PI / n;
		double res = 0.5 * radis * radis * sin(ang) * n;
		printf("%.3lf\n", res);
	}
	return 0;
}
