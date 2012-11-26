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

const int MAXN = 1000 + 10;
int n, m, Min, P;
int indeg[MAXN], outdeg[MAXN], g[MAXN][MAXN], ans[MAXN][5];
int vis[MAXN];

void dfs(int u)
{
	P = u;
	for (int i = 1; i <= n; i++)
	if (u != i && g[u][i])
	{
		Min = min(Min, g[u][i]);
		dfs(i);
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[u][v] = w;
		indeg[v]++;
		outdeg[u]++;
		vis[u] = vis[v] = 1;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	if (indeg[i] == 0 && vis[i])
	{
		Min = 1000000000;
		int k;
		for (int j = 1; j <= n; j++)
		if (i != j && g[i][j])
		{
			k = j;
			Min = min(Min, g[i][j]);
			dfs(j);
			break;
		}
		ans[++cnt][0] = i;
		ans[cnt][1] = P;
		ans[cnt][2] = Min;
	}
	if (cnt == 0) printf("0\n");
	else
	{
		printf("%d\n", cnt);
		for (int i = 1; i <= cnt; i++)
			printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
	}
	return 0;
}
