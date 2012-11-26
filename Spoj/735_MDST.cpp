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
const int MAXM = 1111111;
struct Edge
{
	int v, next;
}edge[MAXM];
int n;
int dis[MAXN][MAXN];
int num, Head[MAXN];

void addEdge(int u, int v)
{
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

queue<int> Q;
void bfs(int u)
{
	memset(dis[u], -1, sizeof(dis[u]));
	dis[u][u] = 0;
	Q.push(u);
	while (!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		for (int i = Head[cur]; i != -1; i = edge[i].next)
		{
			if (dis[u][edge[i].v] == -1)
			{
				dis[u][edge[i].v] = dis[u][cur] + 1;
				Q.push(edge[i].v);
			}
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		num = 0;
		memset(Head, -1, sizeof(Head));

		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			int u, v, k;
			scanf("%d%d", &u, &k);
			while (k--)
			{
				scanf("%d", &v);
				addEdge(u, v);
			}
		}

		int ans = 2000000000;
		for (int i = 1; i <= n; i++)
			bfs(i);
		for (int i = 1; i <= n; i++)
		{
			int s = 0;
			for (int j = 1; j <= n; j++)
				if (dis[i][j] > s)
					s = dis[i][j];
			if (s + s < ans) ans = s + s;
			for (int k = Head[i]; k != -1; k = edge[k].next)
			{
				s = 0;
				for (int j = 1; j <= n; j++)
					if (min(dis[i][j], dis[edge[k].v][j]) > s)
						s = min(dis[i][j], dis[edge[k].v][j]);
				if (s + s + 1 < ans) ans = s + s + 1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
