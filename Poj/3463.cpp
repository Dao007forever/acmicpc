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
const int MAXM = 10000 + 10;
const int INF = 1000000000;
int N, M, S, F, num;
int dis[MAXN][2], cnt[MAXN][2], visit[MAXN][2];
int Head[MAXN];
struct Vertex
{
	int u, flag;
	friend bool operator <(Vertex a, Vertex b)
	{
		return dis[a.u][a.flag] > dis[b.u][b.flag];
	}
};
struct Edge
{
	int v, next, w;
}edge[MAXM * 5];

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

priority_queue<Vertex> Q;
void Dijkstra()
{
	while (!Q.empty())
		Q.pop();
	Vertex s, tmp;
	for (int i = 1; i <= N; i++)
	{
		dis[i][0] = dis[i][1] = INF;
		visit[i][0] = visit[i][1] = false;
		cnt[i][0] = cnt[i][1] = 0;
	}
	dis[S][0] = 0;
	cnt[S][0] = 1;
	s.u = S;
	s.flag = 0;
	Q.push(s);
	while (!Q.empty())
	{
		s = Q.top();
		Q.pop();
		if (visit[s.u][s.flag]) continue;
		visit[s.u][s.flag] = true;
		for (int i = Head[s.u]; i != -1; i = edge[i].next)
		{
			int val = dis[s.u][s.flag] + edge[i].w;
			if (val < dis[edge[i].v][0])
			{
				if (dis[edge[i].v][0] != INF)
				{
					dis[edge[i].v][1] = dis[edge[i].v][0];
					cnt[edge[i].v][1] = cnt[edge[i].v][0];
					tmp.u = edge[i].v; tmp.flag = 1;
					Q.push(tmp);
				}
				dis[edge[i].v][0] = val;
				cnt[edge[i].v][0] = cnt[s.u][s.flag];
				tmp.u = edge[i].v; tmp.flag = 0;
				Q.push(tmp);
			}
			else if (val == dis[edge[i].v][0])
				cnt[edge[i].v][0] += cnt[s.u][s.flag];
			else if (val < dis[edge[i].v][1])
			{
				dis[edge[i].v][1] = val;
				cnt[edge[i].v][1] = cnt[s.u][s.flag];
				tmp.u = edge[i].v; tmp.flag = 1;
				Q.push(tmp);
			}
			else if (val == dis[edge[i].v][1])
				cnt[edge[i].v][1] += cnt[s.u][s.flag];
		}
	}
	int ans = cnt[F][0];
	if (dis[F][0] + 1 == dis[F][1]) ans += cnt[F][1];
	printf("%d\n", ans);
}

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		num = 0;
		memset(Head, -1, sizeof(Head));
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w);
		}
		scanf("%d%d", &S, &F);
		Dijkstra();
	}
	return 0;
}
