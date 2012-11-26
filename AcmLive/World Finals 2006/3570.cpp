#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int inf = 100000000;
int n, m;
int d[111][111], cost[111][111];
int used[111111];
queue<int> que;

void floyd()
{
	for (int k = 0; k < n; k++)
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		if (i != j && j != k && i != k)
			cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
}

void relax(int i, int j, int k)
{
	if (k >= d[i][j]) return;
	d[i][j] = k;
	if (used[i * n + j]) return ;
	used[i * n + j] = 1;
	que.push(i * n + j);
}

int main()
{
	freopen("in", "r", stdin);
	int cas = 1;
	while (scanf("%d%d", &n, &m), n || m)
	{
		printf("Network %d\n", cas++);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				d[i][j] = inf, cost[i][j] = inf;

		while (m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			u--; v--;
			cost[u][v] = 1;
		}

		floyd();

		d[0][0] = 1;
		used[0] = 1;
		while (!que.empty())
			que.pop();
		que.push(0);
		while (!que.empty())
		{
			int cur = que.front();
			int x = cur / n, y = cur % n;
			used[cur] = 0;
			que.pop();

			if (d[x][y] >= d[1][1]) continue;

			relax(y, x, d[x][y] + cost[x][y] - 1);

			for (int k = 0; k < n; k++)
			{
				relax(k, y, d[x][y] + cost[x][k] - (k == y));
				relax(x, k, d[x][y] + cost[k][y] - (k == x));
			}
		}

		if (d[1][1] > n) printf("Impossible\n");
		else printf("Minimum number of nodes = %d\n", d[1][1]);
		puts("");
	}
	return 0;
}
