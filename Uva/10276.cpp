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

const int MAXN = 2000;
int T, N, nx, ny;
int cx[MAXN], cy[MAXN], mk[MAXN], vis[MAXN];
int g[MAXN][MAXN], res[MAXN];

int Path(int u)
{
	for (int v = 1; v <= ny; v++)
	{
		if (g[u][v] && (!mk[v]))
		{
			mk[v] = 1;
			if (!cy[v] || Path(cy[v]))
			{
				cx[u] = v;
				cy[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int MaxMatch()
{
	int ans = 0;
	memset(cx, 0, sizeof(cx));
	memset(cy, 0, sizeof(cy));
	for (int i = 1; i <= nx; i++)
	{
		if (!cx[i])
		{
			memset(mk, 0, sizeof(mk));
			ans += Path(i);
		}
	}
	return ans;
}

int main()
{
	freopen("a", "r", stdin);
	memset(vis, 0, sizeof(vis));
	memset(g, 0, sizeof(g));
	for (int i = 2; i * i < 5000; i++)
		vis[i * i] = true;
	for (int i = 1; i < MAXN; i++)
	for (int j = i + 1; j < MAXN; j++)
		if (vis[i + j]) g[i][j] = 1;

	for (int i = 1; i < MAXN; i++)
	{
		nx = ny = i;
		int temp = MaxMatch();
		res[i - temp] = i;
		if (i - temp > 50) break;
	}

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		printf("%d\n", res[N]);
	}
	return 0;
}
