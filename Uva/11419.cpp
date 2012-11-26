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

const int MAXN = 1111;
int N, M, S;
int cx[MAXN], cy[MAXN], mk[MAXN], adj[MAXN][MAXN], mx[MAXN], my[MAXN];


bool path(int i)
{
	for (int j = 1; j <= M; j++)
	{
		if (adj[i][j] && !mk[j])
		{
			mk[j] = true;
			if (cy[j] == -1 || path(cy[j]))
			{
				cx[i] = j;
				cy[j] = i;
				return true;
			}
		}
	}
	return false;
}

int MaxMatch()
{
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	int res = 0;
	for (int i = 1; i <= N; i++)
	{
		memset(mk, 0, sizeof(mk));
		if (path(i)) res++;
	}
	return res;
}

void DFSX(int x)
{
	for (int y = 1; y <= M; y++)
		if (adj[x][y] && !my[y])
		{
			my[y] = true;
			if (cy[y] != -1) DFSX(cy[y]);
		}
}

void DFSY(int y)
{
	for (int x = 1; x <= N; x++)
		if (adj[x][y] && !mx[x])
		{
			mx[x] = true;
			if (cx[x] != -1) DFSY(cx[x]);
		}
}

void MinCover()
{
	int ans = MaxMatch();
	printf("%d", ans);
	memset(my, 0, sizeof(my));
	for (int i = 1; i <= N; i++)
		if (cx[i] == -1) DFSX(i);
	memset(mx, 0, sizeof(mx));
	for (int i = 1; i <= M; i++)
		if (cy[i] == -1) DFSY(i);
	for (int x = 1; x <= N; x++)
		if (mx[x] || (cx[x] != -1 && !mx[x] && !my[cx[x]]))
			printf(" r%d", x);
	for (int y = 1; y <= M; y++)
		if (my[y])
			printf(" c%d", y);
	printf("\n");
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d%d", &N, &M, &S) != EOF)
	{
		if (N == 0 && M == 0 && S == 0) break;
		memset(adj, 0, sizeof(adj));
		for (int i = 1; i <= S; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u][v] = 1;
		}
		MinCover();
	}
	return 0;
}
