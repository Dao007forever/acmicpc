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

const int MAXN = 555;
const int inf = 100000000;
int N;
int g[MAXN][MAXN], vis[MAXN];

int main()
{
	freopen("a", "r", stdin);
	int u, v;
	int cas = 0;
	while (scanf("%d%d", &u, &v))
	{
		if (u == 0 && v == 0) break;
		printf("Case %d: ", ++cas);
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			g[i][j] = inf;
		g[u][v] = 1;
		N = max(N, u);
		N = max(N, v);
		vis[u] = vis[v] = 1;
		int x, y;
		while (scanf("%d%d", &x, &y))
		{
			if (x == 0 && y == 0) break;
			g[x][y] = 1;
			N = max(N, x);
			N = max(N, y);
			vis[x] = vis[y] = 1;
		}
		for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		if (i != j && i != k && j != k)
			if (g[i][j] > g[i][k] + g[k][j])
				g[i][j] = g[i][k] + g[k][j];
		long long sum = 0;
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		if (i != j && vis[i] && vis[j] && g[i][j] != inf) sum += (long long)g[i][j];
		int cnt = 0;
		for (int i = 1; i <= N; i++)
		if (vis[i]) cnt++;
		double ans = (double)sum / cnt / (cnt - 1);
		printf("average length between pages = %.3lf clicks\n", ans);
	}
	return 0;
}
