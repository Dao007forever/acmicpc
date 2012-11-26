#include <cstdio>
#include <cstring>

const int MAXN = 100 + 10;
int N, M;
int row1[MAXN], row2[MAXN];

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		memset(row1, 0, sizeof(row1));
		memset(row2, 0, sizeof(row2));
		if (N == -1 && M == -1) break;
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			int num;
			scanf("%d", &num);
			if (num)
				row1[i]++;
		}
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			int num;
			scanf("%d", &num);
			if (num)
				row2[i]++;
		}
		bool ok = true;
		for (int i = 1; i <= N; i++)
		if (row1[i] != row2[i] && row1[i] != M - row2[i])
		{
			ok = false;
			break;
		}
		if (ok) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
