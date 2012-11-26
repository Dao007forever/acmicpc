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

const int MAXN = 55;
struct Point
{
	int xmin, xmax, ymin, ymax;
}P[MAXN];
int N, ans;
int g[MAXN][MAXN];
bool mk[MAXN];
int cx[MAXN];

int path(int u)
{
	for (int v = 1; v <= N; v++)
	{
		if (g[u][v] && !mk[v])
		{
			mk[v] = 1;
			if (!cx[v] || path(cx[v]))
			{
				cx[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

void MaxMatch()
{
	for (int i = 1; i <= N; i++)
	{
		memset(mk, 0, sizeof(mk));
		if (path(i)) ans++;
	}
}

int main()
{
	freopen("a", "r", stdin);
	int cas = 0;
	while (scanf("%d", &N) && N)
	{
		memset(g, 0, sizeof(g));
		memset(cx, 0, sizeof(cx));
		cas++;
		printf("Heap %d\n", cas);

		for (int i = 1; i <= N; i++)
		{
			scanf("%d%d%d%d", &P[i].xmin, &P[i].xmax, &P[i].ymin, &P[i].ymax);
		}
		for (int i = 1; i <= N; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			for (int j = 1; j <= N; j++)
			{
				if (x >= P[j].xmin && x <= P[j].xmax && y >= P[j].ymin && y <= P[j].ymax)
					g[i][j] = 1;
			}
		}

		ans = 0;
		MaxMatch();

		int cnt = 0;
		if (ans < N)
		{
			printf("none\n");
			puts("");
			continue;
		}
		for (int i = 1; i <= N; i++)
		{
			int tmp = cx[i];
			cx[i] = 0;
			g[tmp][i] = 0;
			memset(mk, 0, sizeof(mk));
			if (!path(tmp))
			{
				cnt++;
				cx[i] = tmp;
				printf("(%c,%d) ", 'A' + i - 1, tmp);
			}
			g[tmp][i] = 1;
		}
		if (cnt == 0)
			printf("none\n");
		else printf("\n");
		puts("");
	}
	return 0;
}

