#include <cstdio>
#include <cmath>

const double eps = 1e-8;
double H, h, D;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double Calc(double x)
{
	return (h * D - H * x) / (D - x) + x;
}

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%lf%lf%lf", &H, &h, &D);
		double Left, Right, mid, midmid;
		Left = 0, Right = h * D / H;
		while (Right - Left > eps)
		{
			mid = (Left + Right) / 2;
			midmid = (mid + Right) / 2;
			if (dblcmp(Calc(mid) - Calc(midmid)) >= 0)
				Right = midmid;
			else Left = mid;
		}
		printf("%.3lf\n", Calc(Left));
	}
	return 0;
}
