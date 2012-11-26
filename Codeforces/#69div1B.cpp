#include <cstdio>
#include <cmath>

double Solve(int p, int q)
{
	double pp = (double)p, qq = (double) q;
	if (4 * q >= p)
	{
		double s = (qq + qq + 0.25 * pp) * pp * 0.5;
		s = s / (2 * pp * qq);
		return s;
	}
	else
	{
		double s = qq * 4 * qq * 0.5;
		s = s / (2 * pp * qq);
		return 1.0 - s;
	}
}

int main()
{
	freopen("a.txt", "r", stdin);
	int T, p, q;
	scanf("%d", &T);
	while (T--)
	{
		double one = 1;
		double zero = 1;
		scanf("%d%d", &p, &q);
		if (p == 0 && q == 0) printf("%.10lf\n", one);
		else if (q == 0 && p != 0) printf("%.10lf\n", one);
		else if (p == 0 && q != 0) printf("0.5\n");
		else printf("%.10lf\n", Solve(p, q));
	}
	return 0;
}
