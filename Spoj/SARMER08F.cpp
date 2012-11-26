#include <cstdio>

int N;
int F[101];

int main()
{
	freopen("a", "r", stdin);
	F[0] = 0;
	for (int i = 1; i <= 100; i++)
		F[i] = F[i - 1] + i * i;
	while (scanf("%d", &N) != EOF)
	{
		if (N == 0) break;
		printf("%d\n", F[N]);
	}
	return 0;
}
