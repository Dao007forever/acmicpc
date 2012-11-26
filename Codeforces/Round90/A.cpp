#include <cstdio>

int a, b, n;

int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d%d", &a, &b, &n);
	int now = 0;
	while (n)
	{
		int tmp;
		if (!now)
		{
			tmp = gcd(a, n);
			n -= tmp;
		}
		else
		{
			tmp = gcd(b, n);
			n -= tmp;
		}
		now = 1 - now;
	}
	printf("%d", 1 - now);
	return 0;
}
