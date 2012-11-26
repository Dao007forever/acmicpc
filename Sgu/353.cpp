#include <cstdio>

int main()
{
	freopen("a", "r", stdin);
	int N, k1, k2, p1, p2, p3;
	scanf("%d%d%d%d%d%d", &N, &k1, &k2, &p1, &p2, &p3);
	int cnt = 0;
	if (N >= p1)
	{
		N -= p1;
		cnt += k1;
	}
	else N = 0;

	if (N >= p2)
	{
		int tmp = N / p2;
		if (tmp < k2)
		{
			cnt += tmp;
			N -= tmp * p2;
			if (N > 0)
			{
				cnt++;
				N = 0;
			}
		}
		else
		{
			cnt += k2;
			N -= (k2 * p2);
		}
	}
	else if (N > 0)
	{
		cnt++;
		N = 0;
	}

	if (N > 0)
	{
		int tmp = N / p3;
		cnt += tmp;
		N -= tmp * p3;
		if (N > 0) cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}
