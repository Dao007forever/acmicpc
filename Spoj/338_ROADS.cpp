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

const int MAXN = 100 + 10;
const int MAXM = 10000 + 10;
const int inf = 100000000;
struct Edge
{
	int v, w, c, next;
}edge[MAXM];
struct Node
{
	int u, dis, c;
	bool operator < (const Node &a)	const
	{
		return dis > a.dis;
	}
};
int N, M, K;
int num, Head[MAXN];
int dis[MAXN][11111], vis[MAXN][11111];

void addEdge(int u, int v, int w, int c)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].c = c;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int Dijkstra()
{
	priority_queue<Node> Q;
	Node tmp;
	tmp.u = 1, tmp.dis = 0, tmp.c = 0;
	Q.push(tmp);
	while (!Q.empty())
	{
		Node now = Q.top();
		Q.pop();
		if (now.u == N) return now.dis;
		for (int i = Head[now.u]; i != -1; i = edge[i].next)
		if (now.c + edge[i].c <= K)
		{
			tmp.u = edge[i].v;
			tmp.dis = now.dis + edge[i].w;
			tmp.c = now.c + edge[i].c;
			Q.push(tmp);
		}
	}
	return -1;
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
		scanf("%d%d%d", &K, &N, &M);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w, c;
			scanf("%d%d%d%d", &u, &v, &w, &c);
			addEdge(u, v, w, c);
		}
		int ans = Dijkstra();
		printf("%d\n", ans);
	}
	return 0;
}
