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
const int MAXM = 1111;
const int INF = 1000000000;
int N, M, Q;
int dis[MAXN], dist[MAXN][MAXN], use[MAXN], f[MAXN];
int num, Head[MAXN];
struct Edge
{
	int v, w, next;
}edge[4 * MAXM];
struct Vertex
{
	int u, d;
	bool operator <(const Vertex it)const
	{
		return d > it.d;
	}
};

void addEdge(int u, int v, int w)
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
	int start = u;
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
            if (!use[v] && f[v] <= f[start] && dis[u] + edge[i].w < dis[v])
            {
                dis[v] = dis[u] + edge[i].w;
                s.u = v;
                s.d = dis[v];
                Que.push(s);
            }
        }
    }
	for (int i = 1; i <= N; i++)
		dist[start][i] = dis[i];
}

void init()
{
	memset(dist, 0, sizeof(dist));
	memset(f, 0, sizeof(f));
	num = 0;
	memset(Head, -1, sizeof(Head));
}

int main()
{
	freopen("a", "r", stdin);
	int cas = 1;
	int blank = false;
	while (scanf("%d%d%d", &N, &M, &Q))
	{
		if (N == 0 && M == 0 && Q == 0) break;
		if (blank) printf("\n");
		blank = true;
		init();
		printf("Case #%d\n", cas++);
		for (int i = 1; i <= N; i++)
			scanf("%d", &f[i]);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w);
			addEdge(v, u, w);
		}
		for (int i = 1; i <= N; i++)
			Dijkstra(i);
		for (int i = 1; i <= Q; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			int Min = INF, ka, kb, k;
			for (int i = 1; i <= N; i++)
				if (dist[i][a] + dist[i][b] + f[i] < Min)
				{
					Min = dist[i][a] + dist[i][b] + f[i];
					//ka = dist[i][a];
					//kb = dist[i][b];
					//k = i;
				}
			if (Min < INF) printf("%d\n", Min);
			else printf("-1\n");
		}
	}
	return 0;
}
