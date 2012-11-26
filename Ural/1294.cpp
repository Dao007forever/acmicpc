#include <cstdio>
#include <cmath>

const double eps = 1e-8;
double a, b, c, d;

int main()
{
	freopen("a", "r", stdin);
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	a *= 1000.0; b *= 1000.0; c *= 1000.0; d *= 1000.0;
	if (fabs(a * b - c * d) < eps) printf("Impossible.\n");
	else
	{
		double tmp1 = a * b - c * d;
		double tmp2 = (c * c + d * d) * a * b - (a * a + b * b) * c * d;
		double ans = sqrt(tmp2 / tmp1);
		printf("Distance is %.0lf km.\n", ans);
	}
	return 0;
}
