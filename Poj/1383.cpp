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

const int MAXN = 1000 + 10;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int R, C;
char MAP[MAXN][MAXN];
int dis[MAXN][MAXN];

void dfs(int x, int y)
{
	for (int k = 0; k < 4; k++)
	{
		int xx = x + dx[k], yy = y + dy[k];
		if (xx >= 0 && xx < R && yy >= 0 && yy < C && dis[xx][yy] == -1 && MAP[xx][yy] == '.')
		{
			dis[xx][yy] = dis[x][y] + 1;
			dfs(xx, yy);
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &C, &R);
		for (int i = 0; i < R; i++)
			scanf("%s", MAP[i]);

		int flag = true;
		int ki, kj;
		for (int i = 0; i < R && flag; i++)
		{
			for (int j = 0; j < C && flag; j++)
			{
				if (MAP[i][j] == '.')
				{
					ki = i; kj = j;
					flag = false;
					break;
				}
			}
		}

		memset(dis, -1, sizeof(dis));
		dis[ki][kj] = 0;
		dfs(ki, kj);
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (MAP[i][j] == '.')
				{
					if (dis[i][j] > dis[ki][kj])
					{
						ki = i; kj = j;
					}
				}
			}
		}

		memset(dis, -1, sizeof(dis));
		dis[ki][kj] = 0;
		dfs(ki, kj);
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (MAP[i][j] == '.')
				{
					if (dis[i][j] > dis[ki][kj])
					{
						ki = i; kj = j;
					}
				}
			}
		}
		printf("Maximum rope length is %d.\n", dis[ki][kj]);
	}
	return 0;
}
