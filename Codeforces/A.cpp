#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 1000000 + 10;
const double eps = 1e-14;
int t1, t2, x1, x2, t0;
int y2[MAXN];

int sig(double d)
{
	return (d > eps) - (d < -eps);
}

int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d%d%d%d", &t1, &t2, &x1, &x2, &t0);
	if (t1 == t0 && t0 == t2)
	{
		printf("%d %d\n", x1, x2);
	}
	else if (t1 == t0)
	{
		printf("%d 0\n", x1);
	}
	else if (t2 == t0)
	{
		printf("0 %d\n", x2);
	}
	else
	{
		double tmp = (double)(t0 - t1) / (t2 - t0);
		for (int i = x1; i >= 0; i--)
		{
			y2[i] = (int)(tmp * i);
			if (y2[i] > x2) y2[i] = -1;
			else
			{
				double t = (double)(t1 * i + t2 * y2[i]) / (i + y2[i]);
				while (sig(t - t0) < 0) 
				{
					y2[i]++;
					t = (double)(t1 * i + t2 * y2[i]) / (i + y2[i]);
				}
			}
		}
		double ans = 1e99;
		int sum = 0;
		int ans1, ans2;
		for (int i = x1; i >= 0; i--)
		if (y2[i] != -1)
		{
			double t = (double)(t1 * i + t2 * y2[i]) / (i + y2[i]);
			if (sig(t - ans) < 0 || (sig(t - ans) == 0 && i + y2[i] > sum))
			{
				ans = t;
				sum = i + y2[i];
				ans1 = i;
				ans2 = y2[i];
			}
		}
	//	printf("%.3lf\n", ans);
		cout << ans1 << " " << ans2 << endl;
	}
	return 0;
}
