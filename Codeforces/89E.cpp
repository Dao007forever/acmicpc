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

const int MAXN = 5000 + 10;
int L[MAXN], R[MAXN], U[MAXN], D[MAXN];
char g[MAXN][MAXN];
int n, m;
int res1, res2;

int ID(int a, int b)
{
	return (a - 1) * m + b;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", g[i] + 1);
	for (int a = 1; a <= n; a++)
	for (int b = 1; b <= m; b++)
	if (g[a][b] != '.')
	{
		for (int i = 1; i <= n; i++)
		for (int j = 1, pre = 0; j <= m; j++)
		if (g[i][j] != '.')
		{
			L[ID(i, j)] = pre;
			if (pre) R[pre] = ID(i, j);
			R[ID(i, j)] = 0;
			pre = ID(i, j);
		}
		for (int j = 1; j <= m; j++)
		for (int i = 1, pre = 0; i <= n; i++)
		if (g[i][j] != '.')
		{
			U[ID(i, j)] = pre;
			if (pre) D[pre] = ID(i, j);
			D[ID(i, j)] = 0;
			pre = ID(i, j);
		}

		int cnt = 0, x = a, y = b;
		for (;;)
		{
			cnt++;
			int tmp = ID(x, y);
			R[L[tmp]] = R[tmp];
			L[R[tmp]] = L[tmp];
			U[D[tmp]] = U[tmp];
			D[U[tmp]] = D[tmp];
			if (g[x][y] == 'U') tmp = U[tmp];
			else if (g[x][y] == 'D') tmp = D[tmp];
			else if (g[x][y] == 'L') tmp = L[tmp];
			else tmp = R[tmp];
			if (!tmp) break;
			x = (tmp - 1) / m + 1;
			y = (tmp - 1) % m + 1;
		}
		if (cnt > res1)
		{
			res1 = cnt;
			res2 = 1;
		}
		else if (cnt == res1) res2++;
	}
	cout << res1 << " " << res2 << endl;
	return 0;
}

