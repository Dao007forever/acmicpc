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

const int MAXN = 100 + 10;
const int MAXM = 1000 + 10;
int n, m, h;
int a[MAXM];
int dp[MAXM][MAXN];

double C(int n, int m)
{
	double res = 1;
	int a = n, b = m;
	for (int i = 1; i <= n; i++)
	{
		res *= (double)b;
		res /= (double)a;
		a--;
		b--;
	}
	return res;
}

int main()
{
	freopen("d", "r", stdin);
	int s = 0;
	scanf("%d%d%d", &n, &m, &h);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &a[i]);
		s += a[i];
	}

	if (s < n) printf("-1.0\n");
	else
	{
		s--;
		a[h]--;
		n--;
		if (s - a[h] < n)
		{
			printf("1.0\n");
		}
		else
		{
			double t1 = C(n, s - a[h]), t2 = C(n, s);
			double ans = C(n, s - a[h]) / C(n, s);
			ans = 1.0 - ans;
			printf("%.10lf\n", ans);
		}
	}
	return 0;
}
