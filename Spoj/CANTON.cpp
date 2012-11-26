#include <cstdio>
#include <cmath>

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, i, j;
		scanf("%d", &n);
		int p = sqrt(n * 2.0);
		while (p * (p + 1) >= 2 * n)
		{
			p--;
		}
		int sum = p * (p + 1) / 2;
		if (p % 2)
		{
			i = n - sum;
			j = p + 2 - i;
		}
		else
		{
			j = n - sum;
			i = p + 2 - j;
		}
		printf("TERM %d IS %d/%d\n", n, i, j);
	}
	return 0;
}
