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

const int MAXN = 50000 + 1000;
const long long inf = (long long)200000000000;
struct Edge
{
	int v, w, next;
}edge[2 * MAXN];
int N, M, num;
int Head[MAXN], vis[MAXN], weight[MAXN];
long long dis[MAXN];

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void SPFA(int u)
{
	memset(vis, 0, sizeof(vis));
	for (int i = 1 ; i <= N; i++)
		dis[i] = inf;
	dis[u] = 0;
	vis[u] = true;
	queue<int> Q;
	Q.push(u);
	while (!Q.empty())
	{
		int now = Q.front();
		Q.pop();
		for (int i = Head[now]; i != -1; i = edge[i].next)
		{
			int v = edge[i].v;
			if (dis[now] + edge[i].w < dis[v])
			{
				dis[v] = dis[now] + edge[i].w;
				if (!vis[v])
				{
					vis[v] = true;
					Q.push(v);
				}
			}
		}
		vis[now] = false;
	}
}

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		num = 0;
		memset(Head, -1, sizeof(Head));
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
			scanf("%d", &weight[i]);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w);
			addEdge(v, u, w);
		}

		SPFA(1);

		bool flag = true;
		long long res = 0;
		for (int i = 1; i <= N; i++)
		{
			if (dis[i] == inf)
			{
				flag = false;
				break;
			}
			res += dis[i] * (long long)weight[i];
		}
		if (!flag) cout << "No Answer" << endl;
		else cout << res << endl;
	}
	return 0;
}
