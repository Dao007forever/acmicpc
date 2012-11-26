#include <cstdio>
#include <cmath>
#define sqr(x) ((x) * (x))
const double eps = 1e-6;
double A, B, C, X1, x2, Y1, y2;
double x[5], y[5], z[5];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double dist()
{
	return sqrt(sqr(x[1] - x[2]) + sqr(y[1] - y[2]) + sqr(z[1] - z[2]));
}

void change(double x, double y, double &xx, double &yy, double &zz)
{
	if (dblcmp(x) >= 0 && dblcmp(x - C) <= 0 && dblcmp(y - (B + C)) >= 0 && dblcmp(y - (2 * B + C)) <= 0)
	{
		xx = C; yy = y; zz = C - x;
		return;
	}
	else if (dblcmp(x - (A + C)) >= 0 && dblcmp(x - (A + 2 * C)) <= 0 && dblcmp(y - (B + C)) >= 0 && dblcmp(y - (2 * B + C)) <= 0)
	{
		xx = A + C; yy = y; zz = x - (A + C);
		return;
	}
	else if (dblcmp(x - C) >= 0 && dblcmp(x - (A + C)) <= 0 && dblcmp(y) >= 0 && dblcmp(y - (2 * B + 2 * C)) <= 0)
	{
		if (dblcmp(y - B) < 0)
		{
			xx = x; yy = B + C + B - y; zz = C;
			return;
		}
		else if (dblcmp(y - (B + C)) < 0)
		{
			xx = x; yy = B + C; zz = B + C - y;
			return;
		}
		else if (dblcmp(y - (2 * B + C)) < 0)
		{
			xx = x; yy = y; zz = 0;
			return;
		}
		else
		{
			xx = x; yy = 2 * B + C; zz = y - (2 * B + C);
			return;
		}
	}
	xx = x;
	yy = y;
	zz = 0;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%lf%lf%lf", &A, &B, &C);
	scanf("%lf%lf", &X1, &Y1);
	scanf("%lf%lf", &x2, &y2);

	change(X1, Y1, x[1], y[1], z[1]);
	change(x2, y2, x[2], y[2], z[2]);
	printf("%.6lf\n", dist());
	return 0;
}
