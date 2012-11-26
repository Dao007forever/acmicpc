#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 200000 + 10;
int n;
int cnt[maxn], vis[maxn];
int num, Head[maxn];
struct Edge
{
	int v, w, next;
}edge[maxn];
long long res;

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void dfs(int u)
{
	vis[u] = true;
	cnt[u] = 1;
	for (int i = Head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].v;
		if (!vis[v])
		{
			dfs(v);
			cnt[u] += cnt[v];
			res += (long long)edge[i].w * min(cnt[v], n - cnt[v]);
		}
	}
}

int main()
{
	freopen("in", "r", stdin);
	int Test, cas = 1;
	scanf("%d", &Test);
	while (Test--)
	{
		printf("Case #%d: ", cas++);
		num = 0;
		res = 0LL;
		memset(Head, -1, sizeof(Head));
		memset(cnt, 0, sizeof(cnt));
		memset(vis, 0, sizeof(vis));

		scanf("%d", &n);
		for (int i = 1; i < n; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w);
			addEdge(v, u, w);
		}

		dfs(1);
		cout << 2LL * res << endl;
	}
	return 0;
}
