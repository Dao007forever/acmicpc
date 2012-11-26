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

#define REP(i, n) for(i = 0; i < (n); ++i)
#define FOR(i, l, h) for(i = (l); i <= (h); ++i)
#define FORD(i, h, l) for(i = (h); i >= (l); --i)

const int MAXN = 100 + 10;
const int MAXM = 1000 + 10;
int T, N, M, S, E;
bool flag, ok;
int vis[MAXM], kind[MAXN];
int Map[MAXN][MAXN];

void DFS(int u, int s, int limit)
{
	if (u == E)
	{
		if (s <= limit) 
		{
			flag = true;
			ok = true;
			return;
		}
		return;
	}
	if (s > limit) return;
	for (int i = 0; i < N; i++)
	{
		if (Map[u][i] && !vis[kind[i]])
		{
			vis[kind[i]] = 1;
			DFS(i, s + Map[u][i], limit);
			vis[kind[i]] = 0;
		}
	}
}

bool Check(int limit)
{
	flag = false;
	DFS(S, 0, limit);
	return flag;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		memset(kind, 0, sizeof(kind));
		memset(Map, 127, sizeof(Map));
		int Left = 0, Right = 0;
		scanf("%d%d%d%d", &N, &M, &S, &E);
		for (int i = 0; i < M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if (w < Map[u][v])
				Map[u][v] = Map[v][u] = w;
			Right += w;
		}
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &kind[i]);
		}

		if (kind[S] != kind[E])
		{
			ok = false;
			while (Left <= Right)
			{
				memset(vis, 0, sizeof(vis));
				vis[kind[S]] = 1;
				int Mid = (Left + Right) >> 1;
				if (Check(Mid)) Right = Mid - 1;
				else Left = Mid + 1;
			}
		}
		else ok = false;
		if (!ok) printf("%d\n", -1);
		else printf("%d\n", Left);
	}
	return 0;
}
