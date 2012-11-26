#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxt = 10000;
double map[25][25];
int n, s, t;
double p[11111][25];

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d%d", &n, &s, &t);
		memset(map, 0, sizeof(map));
		memset(p, 0, sizeof(p));

		for (int i = 1; i < n; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			map[u][v] = map[v][u] = w;
		}

		p[0][s] = 1;
		double ret = 0;
		for (int i = 0; i < maxt; i++)
		{
			if (p[i][t] > 0) ret += p[i][t] * i;
			p[i][t] = 0;

			for (int j = 1; j <= n; j++)
			if (p[i][j] > 0)
			{
				double sum = 0;
				for (int k = 1; k <= n; k++)
					sum += map[j][k];
				for (int k = 1; k <= n; k++)
				if (map[j][k] > 0)
					p[i + 1][k] += p[i][j] * map[j][k] / sum;
			}
		}
		printf("%.5lf\n", ret);
	}
	return 0;
}
