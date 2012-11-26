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

const int MAXN = 1000000 + 10;
const int MAXM = 4 * MAXN;
const int inf = 1000000000;
struct Edge
{
	int v, w, next;
}edge[MAXM];
struct Vertex
{
	int u, d;
	bool operator <(const Vertex it)const
	{
		return d > it.d;
	}
};
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int N, M, n, num;
int Head[MAXN], dis[MAXN], use[MAXN], a[1111][1111];

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

bool check(int x, int y)
{
	if (x < 1 || x > N || y < 1 || y > M) return false;
	return true;
}

priority_queue<Vertex> Q;
void Dijkstra()
{
	Vertex s;
	for (int i = 1; i <= n; i++)
	{
		use[i] = false;
		dis[i] = inf;
	}
	dis[1] = a[1][1];
	s.u = 1;
	s.d = 0;
	Q.push(s);
	while (!Q.empty())
	{
		s = Q.top();
		Q.pop();
		int u = s.u;
		if (use[u]) continue;
		use[u] = 1;
		for (int i = Head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].v;
			if (!use[v] && dis[u] + edge[i].w < dis[v])
			{
				dis[v] = dis[u] + edge[i].w;
				s.u = edge[i].v;
				s.d = dis[v];
				Q.push(s);
			}
		}
	}
}

int ID(int i, int j)
{
	return (i - 1) * M + j;
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
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				scanf("%d", &a[i][j]);
		n = N * M;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					int x = i + dx[k], y = j + dy[k];
					if (check(x, y)) addEdge(ID(i, j), ID(x, y), a[x][y]);
				}
			}
		Dijkstra();
		printf("%d\n", dis[n]);
	}
	return 0;
}
