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
int N, M, nx, ny;
int res;
int g[MAXN][MAXN], cx[MAXN], cy[MAXN], mk[MAXN];

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

int main()
{
	freopen("a", "r", stdin);
	while (cin >> N && N)
	{
		memset(g, 0, sizeof(g));
		M = 7 * 12;
		nx = N; ny = M;
		for (int i = 1; i <= N; i++)
		{
			int t;
			cin >> t;
			while (t--)
			{
				int a, b;
				cin >> a >> b;
				int tmp = 12 * (a - 1) + b;
				g[i][tmp] = 1;
			}
		}
		MaxMatch();
		cout << res << endl;
	}
	return 0;
}
