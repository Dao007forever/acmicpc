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

const int MAXN = 100 + 10;
int nx, ny;
int jobnum;
int g[MAXN][MAXN], cx[MAXN], cy[MAXN];
int pred[MAXN], Queue[MAXN * MAXN];
int res;

void MaxMatch()
{
	int Head, Tail, y;
	res = 0;
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
}

int main()
{
	freopen("a", "r", stdin);
	int m, i, j;
	while (scanf("%d", &nx))
	{
		if (nx == 0) break;
		scanf("%d%d", &ny, &jobnum);
		memset(g, 0, sizeof(g));
		for (int k = 0; k < jobnum; k++)
		{
			scanf("%d%d%d", &m, &i, &j);
			g[i][j] = 1;
		}
		MaxMatch();
		printf("%d\n", res);
	}
	return 0;
}
