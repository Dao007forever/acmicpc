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

int vis[5555];
char g[5555][5555];
int n;

void dfs(int u, int p)
{
	vis[u] = 1;
	for (int v = 1; v <= n; v++)
	{
		if (g[u][v] == '1')
		{
			if (g[v][p] == '1')
			{
				printf("%d %d %d\n", u, v, p);
				exit(0);
			}
			else if (!vis[v])
			{
				dfs(v, u);
			}
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", g[i] + 1);
	}
	for (int i = 1; i <= n; i++)
	if (!vis[i])
	{
		dfs(i, 0);
	}
	printf("-1\n");
	return 0;
}
