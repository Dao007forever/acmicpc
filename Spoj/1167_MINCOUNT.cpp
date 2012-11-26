#include <cstdio>
#include <iostream>
using namespace std;

unsigned long long n, ans, a, b, c, d;

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%lld", &n);
		a = n / 2;
		b = n % 2;
		n++;
		c = n / 3;
		d = n % 3;
		ans = a * c + (3 * b * c + 2 * a * d + b * d) / 6;
		printf("%lld\n", ans);
	}
	return 0;
}
