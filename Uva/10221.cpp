#include <cstdio>
#include <cmath>
#include <cstring>

const double r = 6440.0;
const double PI = acos(-1.0);
double s, a;
char str[10];

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%lf%lf%s", &s, &a, str) != EOF)
	{
		if (strcmp(str, "deg") == 0)
		{
			if (a > 180.0) a = 360.0 - a;
			a = a / 180.0 * PI;
		}
		else
		{
			a /= 60.0;
			if (a > 180.0) a = 360.0 - a;
			a = a / 180.0 * PI;
		}
		double arc = a * (r + s);
		double chord = (r + s) * sin(0.5 * a) * 2.0;
		printf("%.6lf %.6lf\n", arc, chord);
	}
	return 0;
}
