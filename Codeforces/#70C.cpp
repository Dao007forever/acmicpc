#include <cstdio>

int n, m, k;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d%d", &n, &m, &k);
	int cnt = 0;
	for (int i = 2; i * i <= m; i++)
	{
		if (m % i == 0 && m / i >= k)
		{
			cnt = 1;
			break;
		}
	}
	if (k == 1 && m != 1) cnt = 1;
	if (!cnt) puts("Marsel");
	else if (n & 1) puts("Timur");
	else puts("Marsel");
	return 0;
}
