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
const long long inf = (1LL) << 40;
struct Edge
{
	int to, next;
	long long len;
}edge[2000000];
int N, M, X, Y, tot;
long long dis[MAXN][MAXN], g[MAXN][MAXN], Head[MAXN];
int use[MAXN];

void init()
{
	tot = 0;
	for (int i = 1; i <= N; i++)
		Head[i] = -1;
}

void AddEdge(int u, int v, int w)
{
	edge[tot].to = v;
	edge[tot].len = (long long)w;
	edge[tot].next = Head[u];
	Head[u] = tot++;
}

void spfa(int s)
{
	for (int i = 1; i <= N; i++)
	{
		dis[s][i] = inf;
		use[i] = 0;
	}
	dis[s][s] = 0;
	queue<int> Q;
	Q.push(s);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int i = Head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].to;
			if (dis[s][u] + edge[i].len < dis[s][v])
			{
				dis[s][v] = dis[s][u] + edge[i].len;
				if (!use[v])
				{
					use[v] = 1;
					Q.push(v);
				}
			}
		}
		use[u] = 0;
	}
}

int main()
{
	freopen("a", "r", stdin);
	cin >> N >> M;
	cin >> X >> Y;
	init();
	for (int i = 1; i <= M; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	for (int i = 1; i <= N; i++)
		spfa(i);
	init();
	for (int i = 1; i <= N; i++)
	{
		int x, y;
		cin >> x >> y;
		for (int j = 1; j <= N; j++)
			if (dis[i][j] <= x)
				AddEdge(i, j, y);
	}
	spfa(X);
	if (dis[X][Y] == inf) dis[X][Y] = -1;
	cout << dis[X][Y] << endl;
	return 0;
}
