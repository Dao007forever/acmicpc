#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 100000000;
const int MAXN = 21;
int N, M;
int dis[22][22], price[22];

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			int k, p;
			scanf("%d%d", &k, &p);
			price[k] = p - 1;
		}
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				dis[i][j] = inf;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (price[i] == price[j]) dis[i][j] = 0;
		scanf("%d", &M);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			dis[u][v] = w;
		}
		for (int k = 1; k <= N; k++)
			for (int i = 1; i <= N; i++)
				for (int j = 1; j <= N; j++)
					if (dis[i][k] + dis[k][j] < dis[i][j])
						dis[i][j] = dis[i][k] + dis[k][j];
		for (int j = 1; j <= N; j++)
			for (int i = 1; i <= N; i++)
				if (price[i] + dis[i][j] < price[j])
					price[j] = price[i] + dis[i][j];

		for (int i = 1; i <= N; i++)
			printf("%d %d\n", i, price[i]);
		int ans = 0;
		for (int i = 1; i <= N; i++)
		{
			bool flag = 1;
			for (int j = 1; j <= N; j++)
			{
				for (int k = 1; k <= N; k++)
				if (i != j && j != k && i != k)
				{
					if (price[i] == price[j] + price[k])
					{
						ans++;
						//printf("%d %d %d\n", i, j, k);
						flag = false;
						break;
					}
				}
				if (!flag) break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
