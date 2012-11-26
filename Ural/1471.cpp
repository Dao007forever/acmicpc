#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 50000 + 10;
const int MAXM = 70000 + 10;
int N, M, pos1, pos2;
struct Edge
{
	int v, w, next;
}g[MAXN * 2], Q[MAXN * 2];
int listg[MAXN], listQ[MAXN], p[MAXN], dis[MAXN];
int ans[MAXM];
bool visit[MAXN];

int Find_Set(int x)
{
	if (x != p[x])
		p[x] = Find_Set(p[x]);
	return p[x];
}

void AddG(int a, int b, int c)
{
	g[pos1].next = listg[a];
	g[pos1].v = b;
	g[pos1].w = c;
	listg[a] = pos1++;
}

void AddQ(int a, int b, int c)
{
	Q[pos2].next = listQ[a];
	Q[pos2].v = b;
	Q[pos2].w = c;
	listQ[a] = pos2++;
}

void Tarjan(int u, int now_dis)
{
	dis[u] = now_dis;
	visit[u] = 1;
	int v, w;
	for (int i = listQ[u]; i; i = Q[i].next)
	{
		v = Q[i].v;
		w = Q[i].w;
		if (visit[v])
			ans[w] = dis[u] + dis[v] - 2 * dis[Find_Set(v)];
	}
	for (int i = listg[u]; i; i = g[i].next)
	{
		v = g[i].v;
		w = g[i].w;
		if (!visit[v])
		{
			Tarjan(v, now_dis + w);
			p[v] = u;
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	int a, b, c;
	for (int i = 1; i < N; i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		AddG(a, b, c);
		AddG(b, a, c);
	}
	scanf("%d", &M);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d%d", &a, &b);
		AddQ(a, b, i);
		AddQ(b, a, i);
	}
	Tarjan(0, 0);
	for (int i = 1; i <= M; i++)
		printf("%d\n", ans[i]);
	return 0;
}
