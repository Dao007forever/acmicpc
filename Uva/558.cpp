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
const int MAXM = 2000 + 10;
const int inf = 100000000;
struct Edge
{
	int v, w, next;
}edge[MAXM << 2];
int N, M;
int num, Head[MAXN];
int dis[MAXN], vis[MAXN], cnt[MAXN];

void init()
{
	num = 0;
	memset(Head, -1, sizeof(Head));
	memset(cnt, 0, sizeof(cnt));
}

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

queue<int> Q;
bool Spfa()
{
	while (!Q.empty())
		Q.pop();
	for (int i = 1; i <= N; i++)
	{
		dis[i] = inf;
		vis[i] = false;
	}
	dis[1] = 0;
	vis[1] = true;
	Q.push(1);
	cnt[1]++;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		vis[u] = false;
		for (int i = Head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].v;
			if (dis[u] + edge[i].w < dis[v])
			{
				dis[v] = dis[u] + edge[i].w;
				if (!vis[v])
				{
					Q.push(v);
					cnt[v]++;
					if (cnt[v] > N) return true;
				}
			}
		}
	}
	return false;
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
			u++; v++;
			addEdge(u, v, w);
		}

		bool flag = Spfa();
		if (flag) cout << "possible" << endl;
		else cout << "not possible" << endl;
	}
	return 0;
}
