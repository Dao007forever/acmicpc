#include <cstdio>

const int MAXN = 5000;
const int P = 1988;
int F[MAXN + 10][MAXN + 10];
int N, K;

int main()
{
	freopen("a", "r", stdin);
	for (int i = 0; i <= MAXN; i++)
		F[i][0] = 0;
	for (int i = 0; i <= MAXN; i++)
		F[0][i] = 1;
	for (int i = 1; i <= MAXN; i++)
	{
		for (int j = 1; j <= MAXN; j++)
		{
			if (j > i) F[i][j] = F[i][i];
			else F[i][j] = (F[i - j][j] + F[i][j - 1]) % P;
		}
	}
	while (scanf("%d%d", &N, &K) != EOF)
	{
		if (N == 0 && K == 0) break;
		printf("%d\n", F[N - K][K]);
	}
	return 0;
}
