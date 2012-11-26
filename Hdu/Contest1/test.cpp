#include <cstdio>

int main()
{
	freopen("a", "w", stdout);
	int n = 400, m = 400, l = 1, r = 10000;
	printf("%d %d %d %d\n", n, m, l, r);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			printf("1 ");
		}
		printf("\n");
	}
}
