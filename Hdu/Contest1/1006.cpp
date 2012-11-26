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

const int MAXN = 111;
const int inf = 100000000;
int N;
int M[MAXN], P[MAXN];
int g[MAXN][MAXN], vis[MAXN], dis[MAXN];

void spfa()
{
	for (int i = 1; i <= N; i++)
		dis[i] = inf;
	dis[1] = 0;
	memset(vis, 0, sizeof(vis));
	vis[1] = true;
	queue<int> Q;
	Q.push(1);
	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for (int i = 1; i <= N; i++)
		{
			if (dis[v] + g[v][i] < dis[i])
			{
				dis[i] = dis[v] + g[v][i];
				if (!vis[i])
				{
					vis[i] = true;
					Q.push(i);
				}
			}
		}
		vis[v] = false;
	}
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) != EOF)
	{
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			g[i][j] = inf;
		for (int i = 1; i <= N; i++)
		{
			scanf("%d%d", &M[i], &P[i]);
			for (int j = 1; j <= M[i]; j++)
			{
				int s, l;
				scanf("%d%d", &s, &l);
				s++;
				g[i][s] = g[s][i] = l;
			}
		}

		spfa();
		int Min = inf;
		for (int i = 2; i <= N; i++)
		if (P[i] && dis[i] < Min)
			Min = dis[i];
		printf("%d\n", Min);
	}
	return 0;
}
