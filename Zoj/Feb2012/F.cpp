#include <cmath>
#include <cstdio>

int n, m;

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main()
{
	while (scanf("%d%d", &n, &m) != EOF) {
		double len = sqrt((double)n * n + (double)m * m);
		if (n == m) {
			printf("%.3lf\n", len);
			continue;
		}
		int g = gcd(n, m);
		n /= g; m /= g;
		long long area = (long long)n * m;
		if (area % 2 == 0) {
			double ret = 0.5 * len;
			printf("%.3lf\n", ret);
		} else {
			double ret = 0.5 * (1 + 1 / (double)m / (double)n);
			ret = ret * len;
			printf("%.3lf\n", ret);
		}
	}
	return 0;
}
