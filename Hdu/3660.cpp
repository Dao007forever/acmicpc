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

const int MAXN = 500000 + 10;
const int inf = 100000000;
struct Edge
{
	int v, next, w;
}edge[MAXN];
int N, L, R, num;
int Head[MAXN];
long long dis[MAXN], dp[MAXN];

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void dfs(int u, bool fst)
{
	if (dis[u] > R)
	{
		dp[u] = 0;
		return;
	}
	long long &ans = dp[u];
	if (fst) ans = 0;
	else ans = inf;
	for (int i = Head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].v;
		dis[v] = dis[u] + edge[i].w;
		dfs(v, !fst);
		if (dis[u] + dp[v] + edge[i].w <= R && dis[u] + dp[v] + edge[i].w >= L)
		{
			if (fst)
			{
				if (dp[v] + edge[i].w > ans) ans = dp[v] + edge[i].w;	
			}
			else 
			{
				if (dp[v] + edge[i].w < ans) ans = dp[v] + edge[i].w;
			}
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d%d", &N, &L, &R) != EOF)
	{
		num = 0;
		memset(Head, -1, sizeof(Head));
		memset(dis, 0, sizeof(0));
		for (int i = 1; i < N; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w);
		}
		dfs(0, 1);
		if (dp[0] > R || dp[0] < L) printf("Oh, my god!\n");
		else cout << dp[0] << endl;
	}
	return 0;
}
