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

const int MAXN = 200 + 10;
const int Inf = 0x3f3f3f3f;
const int MAX = 300000;
int Match[MAXN];
int n, m;
int delta, res;
int W[MAXN][MAXN], lx[MAXN], ly[MAXN];
bool visx[MAXN], visy[MAXN];

bool dfs(int x)
{
	visx[x] = true;
	for (int y = 1; y <= n; y++)
	{
		if (visy[y]) continue;
		int temp = lx[x] + ly[y] - W[x][y];
		if (temp == 0)
		{
			visy[y] = true;
			if (Match[y] == -1 || dfs(Match[y]))
			{
				Match[y] = x;
				return true;
			}
		}
		else if (delta > temp) delta = temp;
	}
	return false;
}

void Knuth_Munkres()
{
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	memset(Match, -1, sizeof(Match));
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
		lx[i] = max(lx[i], W[i][j]);
	for (int x = 1; x <= n; x++)
	{
		while (1)
		{
			memset(visx, 0, sizeof(visx));
			memset(visy, 0, sizeof(visy));
			delta = Inf;
			if (dfs(x)) break;
			for (int i = 1; i <= n; i++)
			{
				if (visx[i]) lx[i] -= delta;
				if (visy[i]) ly[i] += delta;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		res += MAX - W[Match[i]][i];
	}
}

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		memset(W, 0, sizeof(W));
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			if (MAX - c > W[a][b])
				W[a][b] = MAX - c;
		}
		res = 0;
		Knuth_Munkres();
		printf("%d\n", res);
	}
	return 0;
}
