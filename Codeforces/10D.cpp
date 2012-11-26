#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 555;
int N, M;
int A[MAXN], B[MAXN];
int pre[MAXN], dp[MAXN], ans[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	scanf("%d", &M);
	for (int i = 1; i <= M; i++)
		scanf("%d", &B[i]);

	for (int i = 1; i <= M; i++)
	{
		int best = 0, k = -1;
		for (int j = 1; j <= N; j++)
		{
			if (A[j] < B[i])
			{
				if (dp[j] > best)
				{
					best = dp[j];
					k = j;
				}
			}
			else if (A[j] == B[i])
			{
				if (best + 1 > dp[j])
				{
					dp[j] = best + 1;
					pre[j] = k;
				}
			}
		}
	}
	int best = 0, pos = -1;
	for (int i = 1; i <= N; i++)
	{
		if (dp[i] > best)
		{
			best = dp[i];
			pos = i;
		}
	}

	printf("%d\n", best);
	if (best)
	{
		int q = 0;
		while (pos != -1)
		{
			ans[q++] = pos;
			pos = pre[pos];
		}
		for (int i = q - 1; i >= 0; i--)
			printf("%d ", A[ans[i]]);
		printf("\n");
	}
	return 0;
}
