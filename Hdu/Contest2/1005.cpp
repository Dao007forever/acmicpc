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
const int MAXM = 200000 + 10;
const int INF = 1000000000;
struct Edge
{
        int v, next, w;
}edge[MAXM * 5];
int N, M;
int Head[MAXN];
int low[MAXN], dfn[MAXN], Index, Top, size;
int vis[MAXM], Stack[MAXN], id[MAXN];
int dis[MAXN][5], use[MAXN][5];
struct Vertex
{
	int u, flag;
	friend bool operator <(Vertex a, Vertex b)
	{
		return dis[a.u][a.flag] > dis[b.u][b.flag];
	}
};

void AddEdge(int u, int v, int w, int num)
{
        edge[num].v = v; edge[num].w = w; edge[num].next = Head[u]; Head[u] = num;
}

void Tarjan(int u)
{
        low[u] = dfn[u] = ++Index;
        Stack[++Top] = u;
        for (int i = Head[u]; i != -1; i = edge[i].next)
        if (!vis[i])
        {
                vis[i] = vis[i ^ 1] = 1;
                if (!dfn[edge[i].v])
                {
                        Tarjan(edge[i].v);
                        low[u] = min(low[u], low[edge[i].v]);
                }
                else low[u] = min(low[u], dfn[edge[i].v]);
        }
        if (low[u] == dfn[u])
        {
                size++;
                for (;Stack[Top + 1] != u; --Top)
                        id[Stack[Top]] = size;
        }
}

priority_queue<Vertex> Que;
void Dijkstra(int u)
{
	while (!Que.empty())
		Que.pop();
    Vertex s, tmp;
    for (int i = 1; i <= N; i++)
    {
        use[i][0] = use[i][1] = false;
        dis[i][0] = dis[i][1] = INF;
    }
    dis[u][0] = 0;
    s.u = u;
    s.flag = 0;
    Que.push(s);
    while (!Que.empty())    
    {
        s = Que.top();
        Que.pop();
        if (use[s.u][s.flag]) continue;
        use[s.u][s.flag] = true;
        for (int i = Head[s.u]; i != -1; i = edge[i].next)
        {
            int val = dis[s.u][s.flag] + edge[i].w;
			if (val < dis[edge[i].v][0])
			{
				if (dis[edge[i].v][0] != INF)
				{
					dis[edge[i].v][1] = dis[edge[i].v][0];
					tmp.u = edge[i].v;
					tmp.flag = 1;
					Que.push(tmp);
				}
				dis[edge[i].v][0] = val;
				tmp.u = edge[i].v; tmp.flag = 0;
				Que.push(tmp);
			}
			else if (val < dis[edge[i].v][1])
			{
				dis[edge[i].v][1] = val;
				tmp.u = edge[i].v; tmp.flag = 1;
				Que.push(tmp);
			}
        }
    }
	printf("%d\n", dis[N][1]);
}

void init()
{
	Index = Top = size = 0;
	memset(Head, -1, sizeof(Head));
	memset(id, 0, sizeof(id));
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(vis, 0, sizeof(vis));
	memset(Stack, 0, sizeof(Stack));
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		init();
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			int m1 = 2 * i, m2 = m1 ^ 1;
			AddEdge(u, v, w, m1);
			AddEdge(v, u, w, m2);
		}
		for (int i = 1; i <= N; i++)
		if (!dfn[i]) Tarjan(i);

		if (id[1] != id[N])
		{
			puts("-1");
			continue;
		}

		Dijkstra(1);
	}
	return 0;
}
