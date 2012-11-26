#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
const int INF = 2000000000;
struct Vertex
{
	int u, d;
	bool operator <(const Vertex it)const
	{
		return d > it.d;
	}
};
struct Edge {
	int v, w, next;
}edge[4 * maxn];
int n, m, s;
int dis[maxn], use[maxn];
int num, Head[maxn];

priority_queue<Vertex> Que;
void Dijkstra(int u)
{
    Vertex s;
    for (int i = 1; i <= n; i++)
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
                s.u = v;
                s.d = dis[v];
                Que.push(s);
            }
        }
    }
}

void addEdge(int u, int v, int w) {
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int main() {
	freopen("in.txt", "r", stdin);
	num = 0;
	memset(Head, -1, sizeof(Head));
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	Dijkstra(s);
	int l;
	scanf("%d", &l);
	int ret = 0, cnt = 0;
	for (int i = 1; i <= n; i++)
		if (dis[i] <= l) {
			if (dis[i] == l) {
				ret++;
				continue;
			}
			else {
				for (int j = Head[i]; j != -1; j = edge[j].next) {
					int v = edge[j].v;
					if (dis[i] + edge[j].w > l) {
						if (edge[j].w >= 2 * (l - dis[i])) ret++;
						if (dis[v] < l && edge[j].w == 2 * (l - dis[i])) cnt++;
					}
				}
			}
	}
	printf("%d\n", ret - cnt / 2);
	return 0;
}
