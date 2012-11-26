#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 410;
int N, M;
int val[MAXN], dp[MAXN / 2][MAXN], F[MAXN / 2][MAXN];
bool visit[MAXN];
vector<int> son[MAXN / 2];

void dfs(int root)
{
	if (visit[root]) return;
	visit[root] = true;
	F[root][0] = 0;
	for (int i = 0; i < son[root].size(); i++)
	{
		int u = son[root][i];
		for (int j = M; j >= 0; j--)
		{
			for (int k = 1; j + k <= M; k++)
			{
				if (F[root][j] != -1)
				{
					if (!visit[u]) dfs(u);
					if (dp[u][k] != -1)
						F[root][j + k] = max(F[root][j + k], F[root][j] + dp[u][k]);
				}
			}
		}
	}
	for (int i = 0; i <= M; i++)
	{
		if (F[root][i] != -1)
			dp[root][i + 1] = F[root][i] + val[root];
	}
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		if (N == 0 && M == 0) break;
		for (int i = 0; i <= N; i++)
			son[i].clear();
		for (int i = 1; i <= N; i++)
		{
			int r;
			scanf("%d%d", &r, &val[i]);
			son[r].push_back(i);
		}
		val[0] = 0;
		memset(dp, -1, sizeof(dp));
		memset(F, -1, sizeof(F));
		memset(visit, 0, sizeof(visit));
		dfs(0);
		printf("%d\n", dp[0][M + 1]);
	}
	return 0;
}
