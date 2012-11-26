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
const int INF = 100000000;
struct Edge
{
	int v, w, next;
	int vis, in;
}edge[MAXM * 2];
int N, M, cnt, ans;
int Head[MAXN], dis[MAXN], use[MAXN], pre[MAXN], preedge[MAXN], sel[MAXM];
struct Vertex
{
	int u, d;
	bool operator <(const Vertex it)const
	{
		return d > it.d;
	}
};

void addEdge(int u, int v, int w, int num)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num;
}

void init()
{
	cnt = 0;
	ans = 0;
	memset(Head, -1, sizeof(Head));
	memset(edge, 0, sizeof(edge));
	memset(sel, 0, sizeof(sel));
}

priority_queue<Vertex> Que;
void Dijkstra(int u, bool yes)
{
	while (!Que.empty())
		Que.pop();
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
		if (!edge[i].vis)
        {
            int v = edge[i].v;
            if (!use[v] && dis[u] + edge[i].w < dis[v])
            {
                dis[v] = dis[u] + edge[i].w;
                pre[v] = u;
				preedge[v] = i;
                s.u = v;
                s.d = dis[v];
                Que.push(s);
            }
        }
    }
	if (yes)
	{
		if (dis[N] == INF) ans = INF;
		else if (dis[N] > ans) ans = dis[N];
	}
}

void build(int v)
{
	while (pre[v] != 0)
	{
		sel[cnt++] = preedge[v];
		v = pre[v];
	}
}

void solve()
{
	for (int i = 0; i < cnt; i++)
	{
		edge[sel[i]].vis = true;
		if (sel[i] % 2 == 0) edge[sel[i] + 1].vis = true;
		else edge[sel[i] - 1].vis = true;
		Dijkstra(1, true);
		edge[sel[i]].vis = false;
		if (sel[i] % 2 == 0) edge[sel[i] + 1].vis = false;
		else edge[sel[i] - 1].vis = false;
	}
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
			addEdge(u, v, w, 2 * i);
			addEdge(v, u, w, 2 * i + 1);
		}
		Dijkstra(1, false);
		build(N);
		solve();
		if (ans == INF) printf("-1\n");
		else printf("%d\n", ans);
	}
	return 0;
}
