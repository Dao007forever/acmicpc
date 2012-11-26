#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100 + 10;
int N, M;
double g[MAXN][MAXN];

void Floyd()
{
	for (int k = 1; k <= N; k++)
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (i != k && i != j && j != k)
		if (g[i][k] && g[k][j])
		if (g[i][k] * g[k][j] > g[i][j])
			g[i][j] = g[i][k] * g[k][j];
}

int main()
{
//	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		scanf("%d", &M);
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			g[u][v] = g[v][u] = w * 1.0 / 100;
		}
		Floyd();
		printf("%.6lf percent\n", g[1][N] * 100.0);
	}
	return 0;
}
