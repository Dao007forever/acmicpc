#include <cstdio>

int ans[5555];

char toch(int x)
{
	if (x < 26) return x + 'A';
	return (x - 26 + 'a');
}

int main()
{
	int n;
	bool blank = false;
	while (scanf("%d", &n) != EOF)
	{
		if (blank) puts("");
		blank = true;
		printf("2 %d %d\n", n, n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				printf("%c", toch(i));
			puts("");
		}
		puts("");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				printf("%c", toch(j));
			puts("");
		}
	}
	return 0;
}
