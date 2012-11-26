#include <cstdio>

int n, m;

int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main()
{
	scanf("%d%d", &n, &m);
	n--; m--;
	int res = n + m - gcd(n, m);
	printf("%d\n", res);
	return 0;
}
