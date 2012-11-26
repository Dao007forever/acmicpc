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

const int MAXN = 111;
struct Edge
{
	int v, next;
}edge[1111111];
int R, C, nx, ny;
int num, Head[MAXN * MAXN];
int cx[MAXN * MAXN], cy[MAXN * MAXN], mk[MAXN * MAXN];
int LMap[MAXN][MAXN], RMap[MAXN][MAXN];
char Map[MAXN][MAXN];

int path(int u)
{
	for (int i = Head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].v;
		if (!mk[v])
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

void MaxMatch()
{
	int res = 0;
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
	printf("%d\n", res);
}

void addEdge(int u, int v)
{
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		num = 0;
		memset(Head, -1, sizeof(Head));
		memset(LMap, 0, sizeof(LMap));
		memset(RMap, 0, sizeof(RMap));
		scanf("%d%d", &R, &C);
		for (int i = 0; i < R; i++)
		{
			scanf("%s", Map[i]);
		}

		nx = 0;
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (Map[i][j] == '*')
				{
					LMap[i][j] = ++nx;
					while (j + 1 < C && Map[i][j + 1] == '*')
					{
						j++;
						LMap[i][j] = nx;
					}
				}
				//if (Map[i][j] == '*' && Map[i][j + 1] != '*')
				//	nx++;
			}
		}
		ny = 0;
		for (int j = 0; j < C; j++)
		{
			for (int i = 0; i < R; i++)
			{
				if (Map[i][j] == '*')
				{
					RMap[i][j] = ++ny;
					while (i + 1 < R && Map[i + 1][j] == '*')
					{
						i++;
						RMap[i][j] = ny;
					}
				}
				//if (Map[i][j] == '*' && Map[i + 1][j] != '*')
				//	ny++;
			}
		}
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (Map[i][j] == '*')
				{
					//g[LMap[i][j]][RMap[i][j]] = 1;
					addEdge(LMap[i][j], RMap[i][j]);
				}
			}
		}
		MaxMatch();
	}
	return 0;
}
