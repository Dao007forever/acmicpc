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

struct Point
{
	double x[6];
	void input()
	{
		for (int i = 0; i < 5; i++)
			scanf("%lf", x + i);
	}
	double calDis(int mask)
	{
		double res = x[4];
		for (int i = 0; i < 4; i++)
		{
			if ((mask >> i) & 1) res += x[i];
			else res -= x[i];
		}
		return res;
	}
};
Point ps[100010];
int n;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		ps[i].input();
	double ans = -1.0;
	for (int mask = 0; mask < 16; mask++)
	{
		double maxDis = -100000000000000.0, minDis = 100000000000000.0;
		for (int i = 0; i < n; i++)
		{
			double tmp = ps[i].calDis(mask);
			maxDis = max(maxDis, tmp);
			minDis = min(minDis, tmp);
		}
		ans = max(ans, maxDis - minDis);
	}
	printf("%.2f\n", ans);
	return 0;
}
