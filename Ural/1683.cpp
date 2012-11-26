#include <cstdio>

int N;
int tot;
int ans[101];

int main()
{
	scanf("%d", &N);
	tot = 0;
	while (N > 1)
	{
		N = N - (N >> 1);
		ans[++tot] = N;
	}
	printf("%d\n", tot);
	for (int i = 1; i <= tot; i++)
		printf("%d ", ans[i]);
	return 0;
}
