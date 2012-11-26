
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

#define REP(i, n) for(i = 0; i < (n); ++i)
#define FOR(i, l, h) for(i = (l); i <= (h); ++i)
#define FORD(i, h, l) for(i = (h); i >= (l); --i)

const int MAXN = 500 + 10;
int N, M;
int nx, ny, res;
int g[MAXN][MAXN], cx[MAXN], cy[MAXN], mk[MAXN];

int Path(int u)
{
	int v;
	FOR(v, 1, ny)
	{
		if (g[u][v] > 0 && (!mk[v]))
		{
			mk[v] = 1;
			if (!cy[v] || Path(cy[v]))
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
	int i;
	FOR(i, 1, nx)
	{
		if (!cx[i])
		{
			memset(mk, 0, sizeof(mk));
			res += Path(i);
		}
	}
	return 0;
}

int main()
{
	freopen("a", "r", stdin);
	memset(g, 0, sizeof(g));
	cin >> N >> M;
	int i;
	REP(i, M)
	{
		int u, v;
		cin >> u >> v;
		g[u][v] = 1;
	}
	nx = N;
	ny = N;
	MaxMatch();
	cout << res << endl;
	return 0;
}
