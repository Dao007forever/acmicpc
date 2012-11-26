#include <cstdio>
#include <cmath>

const double Pi = acos(-1.0);

int main()
{
	freopen("a", "r", stdin);
	double r, r1, h;
	while (scanf("%lf%lf", &h, &r) != EOF)
	{
		r1 = r / 100;
		double a = asin(r1 / (4 * h));
		a = a * 180 / Pi;
		printf("%.2lf\n", a);
	}
	return 0;
}
