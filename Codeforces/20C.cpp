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

const int MAXN = 222222;
const long long INF = 1000000000000000LL;
int N, M, num;
struct Edge
{
	int v, next;
	long long w;
}edge[MAXN];
struct Vertex
{
	int u, d;
	bool operator <(const Vertex it)const
	{
		return d > it.d;
	}
};
long long dis[MAXN];
int use[MAXN], pre[MAXN], Head[MAXN];

void addEdge(int u, int v, long long w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

priority_queue<Vertex> Que;
void Dijkstra(int u)
{
	Vertex s;
	for (int i = 1; i <= N; i++)
	{
		use[i] = false;
		dis[i] = INF;
	}
	dis[u] = 0;
	s.u = u;
	s.d = 0;
	Que.push(s);
	while (!Que.empty())	
	{
		s = Que.top();
		Que.pop();
		u = s.u;
		if (use[u]) continue;
		use[u] = true;
		for (int i = Head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].v;
			if (!use[v] && dis[u] + edge[i].w < dis[v])
			{
				dis[v] = dis[u] + edge[i].w;
				pre[v] = u;
				s.u = v;
				s.d = dis[v];
				Que.push(s);
			}
		}
	}
}

void output(int i)
{
	if (pre[i] != -1)
	{
		output(pre[i]);
	}
	printf("%d ", i);
}

int main()
{
	freopen("a", "r", stdin);
	num = 0;
	memset(Head, -1, sizeof(Head));
	memset(pre, -1, sizeof(pre));
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	Dijkstra(1);
	if (pre[N] == -1) puts("-1");
	else output(N);
	return 0;
}
