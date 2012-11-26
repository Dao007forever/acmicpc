#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int n, k, t;
double Max, Min;
int a[111], v[111];
int b[111];

void solve()
{
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	if (!v[i])
	{
		b[cnt++] = a[i];
	}
	sort(b, b + cnt);
	double Sum1 = 0.0, Sum2 = 0.0;
	for (int i = 0; i < t; i++)
	{
		Sum1 += b[i];
		Sum2 += b[cnt - i - 1];
	}
	Min = min(Min, Sum1 / t);
	Max = max(Max, Sum2 / t);
}
int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &k);
	t = n / k;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int q;
	scanf("%d", &q);
	int cnt = q;
	Max = -1.0, Min = 1e10;
	for (int i = 1; i <= q; i++)
	{
		double Sum = 0.0;
		int flag = false;
		for (int j = 1; j <= t; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			if (v[tmp]) flag = true;
			v[tmp] = 1;
			Sum += (double)a[tmp];
		}
		if (flag) cnt--;
		double tmp = Sum / t;
		Max = max(tmp, Max);
		Min = min(tmp, Min);
	}
	if (cnt < k) solve();
	printf("%.10lf %.10lf\n", Min, Max);
	return 0;
}
