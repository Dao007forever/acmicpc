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

const int MAXN = 300 + 10;
int T, nx, ny;
int jobnum;
int g[MAXN][MAXN], cx[MAXN], cy[MAXN];
int pred[MAXN], Queue[MAXN * MAXN];
int res;

int MaxMatch()
{
	int Head, Tail, y;
	int res = 0;
	memset(cx, 0xff, sizeof(cx));
	memset(cy, 0xff, sizeof(cy));
	for (int i = 1; i <= nx; i++)
	{
		if (cx[i] != -1) continue;
		for (int j = 1; j <= ny; j++)
			pred[j] = -2;
		Head = Tail = 0;
		for (int j = 1; j <= ny; j++)
		{
			if (g[i][j])
			{
				pred[j] = -1;
				Queue[Tail++] = j;
			}
		}
		while (Head < Tail)
		{
			y = Queue[Head];
			if (cy[y] == -1) break;
			Head++;
			for (int j = 1; j <= ny; j++)
			{
				if (pred[j] == -2 && g[cy[y]][j])
				{
					pred[j] = y;
					Queue[Tail++] = j;
				}
			}
		}
		if (Head == Tail) continue;
		while (pred[y] > -1)
		{
			cx[cy[pred[y]]] = y;
			cx[y] = cy[pred[y]];
			y = pred[y];
		}
		cy[y] = i;
		cx[i] = y;
		res++;
	}
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &nx, &ny);
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= nx; i++)
		{
			int num;
			scanf("%d", &num);
			for (int j = 1; j <= num; j++)
			{
				int t;
				scanf("%d", &t);
				g[i][t] = 1;
			}
		}
		if (MaxMatch() == nx) printf("YES\n");
		else printf("NO\n");
	}
}
