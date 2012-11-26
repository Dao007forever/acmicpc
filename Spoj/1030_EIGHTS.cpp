#include <cstdio>

int p[1111];
int cnt;

int main()
{
	freopen("in", "r", stdin);
	cnt = 0;
	for (int i = 0; i < 1000; i++)
		if (i * i * i % 1000 == 888)
			p[cnt++] = i;
	long long k;
	int Test;
	for (scanf("%d", &Test); Test; Test--)
	{
		scanf("%lld", &k);
		printf("%lld\n", (k - 1) / 4 * 1000 + p[(k - 1) % 4]);
	}
	return 0;
}
