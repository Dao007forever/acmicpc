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

const int MAXN = 444;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int n, m, N, M, S;
int cx[MAXN], cy[MAXN], mk[MAXN], adj[MAXN][MAXN], id[MAXN][MAXN];


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

bool check(int x, int y)
{
	if (x < 1 || x > n || y < 1 || y > m) return false;
	return true;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		memset(adj, 0, sizeof(adj));
		scanf("%d%d", &n, &m);
		char str[111][111];
		for (int i = 1; i <= n; i++)
			scanf("%s", str[i] + 1);
		int num = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (str[i][j] == '*') id[i][j] = ++num;
		N = n * m; M = n * m;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			if (str[i][j] == '*')
			{
				for (int k = 0; k < 4; k++)
				{
					int x = i + dx[k], y = j + dy[k];
					if (check(x, y) && str[x][y] == '*')
					{
						adj[id[i][j]][id[x][y]] = 1;
						adj[id[x][y]][id[i][j]] = 1;
						//cout << id[i][j] << " " << id[x][y] << endl;
					}
				}
			}
		int res = MaxMatch();
		printf("%d\n", num - res / 2);
	}
	return 0;
}
