#include <cstdio>

int main()
{
	int n;
	scanf("%d", &n);
	int i4 = 0, i7 = 0;
	for (; i7 * 7 < n; i7++);
	while (i7 != -1)
	{
		if (i7 * 7 + i4 * 4 == n)
		{
			for (int i = 0; i < i4; i++)
				printf("4");
			for (int i = 0; i < i7; i++)
				printf("7");
			return 0;
		}
		i7--;
		for (; i7 * 7 + i4 * 4 < n; i4++);
	}
	printf("-1");
	return 0;
}
