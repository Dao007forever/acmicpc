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
const int MAXM = 100000 + 10;
const int inf = 1000000000;
struct node
{
	int v, time;
};
struct cmp
{
	bool operator()(node a, node b)
	{
		return a.time > b.time;
	}
};
priority_queue<node, vector<node>, cmp> que;
struct edge
{
	int v, t, next;
};
edge g[MAXM], re[MAXM];
int N, M, S, D, K, num1, num2;
int vis[MAXN], dist[MAXN], visited[MAXN], H[MAXN], R[MAXN];

void AddEdge1(int u, int v, int t)
{
	g[num1].v = v;
	g[num1].t = t;
	g[num1].next = H[u];
	H[u] = num1++;
}

void AddEdge2(int u, int v, int t)
{
	re[num2].v = v;
	re[num2].t = t;
	re[num2].next = R[u];
	R[u] = num2++;
}

void Dijkstra(int s, int n)
{
	node temp;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)
		dist[i] = inf;
	temp.v = s;
	temp.time = 0;
	dist[s] = 0;
	while (!que.empty())
		que.pop();
	que.push(temp);
	while (!que.empty())
	{
		temp = que.top();
		que.pop();
		int v = temp.v, t = temp.time;
		vis[v] = 1;
		for (int i = R[v]; i != -1; i = re[i].next)
		{
			int u = re[i].v, w = re[i].t;
			if (!vis[u] && dist[v] + w < dist[u])
			{
				dist[u] = dist[v] + w;
				temp.v = u;
				temp.time = dist[u];
				que.push(temp);
			}
		}
	}
	return;
}

int A_Star(int s, int end, int k, int n)
{
	Dijkstra(end, n);
	node temp;
	memset(visited, 0, sizeof(visited));
	temp.v = s, temp.time = dist[s];
	if (s == end)
		visited[s] = -1;
	while (!que.empty())
		que.pop();
	que.push(temp);
	while (!que.empty())
	{
		temp = que.top();
		que.pop();
		int v = temp.v, t = temp.time;
		visited[v]++;
		if (visited[v] == k) return t;
		if (visited[v] > k) continue;
		for (int i = H[v]; i != -1; i = g[i].next)
		{
			int u = g[i].v, w = g[i].t;
			temp.v = u, temp.time = t - dist[v] + w + dist[u];
			que.push(temp);
		}
	}
	return -1;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		g[i].v = 0; g[i].next = 0;
		re[i].v = 0; re[i].next = 0;
	}
	memset(H, -1, sizeof(H));
	memset(R, -1, sizeof(R));
	
	num1 = 0;
	num2 = 0;
	for (int i = 1; i <= M; i++)
	{
		int a, b, t;
		scanf("%d%d%d", &a, &b, &t);
		AddEdge1(a, b, t);
		AddEdge2(b, a, t);
	}

	scanf("%d%d%d", &S, &D, &K);
	printf("%d\n", A_Star(S, D, K, N));
	return 0;
}
