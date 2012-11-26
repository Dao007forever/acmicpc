#include <cstdio>
#include <cmath>

const double PI = acos(-1.0);
double a, b, c;

double area(double x, double y, double z)
{
	double p = (x + y + z) / 2;
	return sqrt(p * (p - x) * (p - y) * (p - z));
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%lf%lf%lf", &a, &b, &c);
		double l = 0, r = a + b;
		for (int i = 0; i < 100; i++)
		{
			double mid = (l + r) / 2.0;

			double x0 = mid / 2, y0 = sqrt(3) * x0;

			double y = area(a, b, mid) * 2 / mid, x = sqrt(a*a - y*y);
			//double x=(mid-(b*b-a*a)/mid)/2;
			//double y=sqrt(a*a-x*x);
//			double ang = (a*a + mid*mid - b*b) / (2*a*mid);
//			double y = a * sin(ang), x = sqrt(a*s - y*y);

			if (x < mid && atan2(y, x) <= PI / 3 && atan2(y, mid - x) <= PI / 3)
			{
				double dist = (x - x0) * (x - x0) + (y - y0) * (y - y0);
				if (dist <= c * c) l = mid;
				else r = mid;
			}
			else l = mid;
		}
		printf("%.2lf\n", l * l * sqrt(3) / 4);
	}
	return 0;
}
