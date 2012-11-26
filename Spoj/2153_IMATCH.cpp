#include <cstdio>

int n, m;
double s;
double map[222][222];
int flag[222];

inline void solve(int Test)
{
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
		if (map[i][k])
		{
			for (int j = 1; j <= n; j++)
			if (map[i][k] * map[k][j] > map[i][j])
				map[i][j] = map[i][k] * map[k][j];
		}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (map[i][j]) map[i][j] = 1 / map[i][j];
			else map[i][j] = 1e99;

	for (int k = 1; k <= n; k++)
		if (flag[k] == Test)
			for (int i = 1; i <= n; i++)
			if (map[i][k] < map[1][2])
				for (int j = 1; j <= n; j++)
					if (map[i][k] + map[k][j] < map[i][j])
						map[i][j] = map[i][k] + map[k][j];
	printf("%.8lf\n", s * map[1][2]);
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				scanf("%lf", &map[i][j]);
				map[i][j] /= 100;
			}
		scanf("%d", &m);
		for (int i = 1; i <= m; i++)
		{
			int k;
			scanf("%d", &k);
			flag[k] = Test;
		}
		scanf("%lf", &s);
		solve(Test);
	}
	return 0;
}
