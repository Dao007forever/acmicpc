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

const int MAXN = 2000 + 10;
struct Client
{
	int a, b;
	double k;
}c[MAXN];
int n, B;
double dp[MAXN], sa[MAXN], sb[MAXN];

bool cmp(const Client &a, const Client &b)
{
	return a.k < b.k;
}

void init()
{
	scanf("%d%d", &B, &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &c[i].a, &c[i].b);
		c[i].k = (double)c[i].a / (double)c[i].b;
	}
	sort(c + 1, c + n + 1, cmp);
	sa[0] = sb[0] = 0.0;
	for (int i = 1; i <= n; i++)
	{
		sa[i] = sa[i - 1] + c[i].a;
		sb[i] = sb[i - 1] + c[i].b;
	}
}

double calc(int i, int j)
{
	double a = -(sb[j] - sb[i - 1]), b = sa[j] - sa[i - 1];
	double x = -b / 2 / a;
	if (x > c[i].k) x = c[i].k;
	return a * x * x + b * x;
}

void solve()
{
	for (int i = 1; i <= n; i++)
	{
		dp[i] = dp[i - 1];
		for (int j = 1; j <= i; j++)
		{
			double tmp = dp[j - 1] + calc(j, i) - B;
			if (tmp > dp[i]) dp[i] = tmp;
		}
	}
	printf("%.9lf\n", dp[n]);
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		init();
		solve();
	}
	return 0;
}
