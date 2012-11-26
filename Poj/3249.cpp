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

const int MAXN = 100000 + 10;
const int MAXM = 1000000 + 10;
const int inf = 1000000000;
struct Edge
{
	int v, next;
}edge[MAXM];
int N, M, num;
int cost[MAXN], Head[MAXN], indeg[MAXN], outdeg[MAXN], dp[MAXN];
int vis[MAXN];

void addEdge(int u, int v)
{
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void init()
{
	for (int i = 1; i <= N; i++)
	if (!indeg[i])
		dp[i] = cost[i];
	else dp[i] = -inf;
}

void Top_DP()
{
	int tot = 1;
	while (tot < N)
	{
		for (int u = 1; u <= N; u++)
		{
			if (!indeg[u] && !vis[u])
			{
				vis[u] = true;
				tot++;
				for (int i = Head[u]; i != -1; i = edge[i].next)
				{
					int v = edge[i].v;
					indeg[v]--;
					if (dp[u] + cost[v] > dp[v])
						dp[v] = dp[u] + cost[v];
				}
			}
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		num = 0;
		memset(Head, -1, sizeof(Head));
		memset(indeg, 0, sizeof(indeg));
		memset(outdeg, 0, sizeof(outdeg));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= N; i++)
			scanf("%d", &cost[i]);
		for (int i = 1; i <= M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			outdeg[u]++;
			indeg[v]++;
			addEdge(u, v);
		}
		int ans = -inf;
		init();
		Top_DP();
		for (int i = 1; i <= N; i++)
		if (!outdeg[i] && dp[i] > ans)
		{
			ans = dp[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
