#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 400 + 10;
int nx, ny, res;
int x1[MAXN], y1[MAXN], x2[MAXN], y2[MAXN];
int cx[MAXN], cy[MAXN], mk[MAXN], g[MAXN][MAXN];

int abs(int x)
{
	if (x < 0) return -x;
	return x;
}
int path(int u)
{
        for (int v = 1; v <= ny; v++)
        {
                if (g[u][v] > 0 && (!mk[v]))
                {
                        mk[v] = 1;
                        if (!cy[v] || path(cy[v]))
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
        res = 0;
        memset(cx, 0, sizeof(cx));
        memset(cy, 0, sizeof(cy));
        for (int i = 1; i <= nx; i++)
        {
                if (!cx[i])
                {
                        memset(mk, 0, sizeof(mk));
                        res += path(i);
                }
        }
        return 0;
}

int dist(int i, int j)
{
	return abs(x1[i] - x2[j]) + abs(y1[i] - y2[j]);
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		int s, t;
		scanf("%d%d%d%d", &nx, &ny, &s, &t);
		s = s * t / 200;
		for (int i = 1; i <= nx; i++)
			scanf("%d%d", &x1[i], &y1[i]);
		for (int i = 1; i <= ny; i++)
			scanf("%d%d", &x2[i], &y2[i]);

		for (int i = 1; i <= nx; i++)
			for (int j = 1; j <= ny; j++)
				g[i][j] = (dist(i, j) <= s);
		MaxMatch();
		printf("%d\n", res);
	}
	return 0;
}
