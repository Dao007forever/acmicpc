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

const int MAXN = 200 + 10;
int N, M;
int n;
int a[MAXN * MAXN][2];
int p[MAXN * MAXN], sum[MAXN * MAXN];

int getfather(int x)
{
	if (p[x] != x) p[x] = getfather(p[x]);
	return p[x];
}

int Check(int x, int y)
{
	return (getfather(x) == getfather(y)) ? 1 : 0;
}

int ID(int i, int j)
{
	return i * (M + 1) + j;
}

void MakeGraph(int side)
{
	int ul, ur, dl, dr;
	char ch;
	int i, j;
	REP(i, N)
	REP(j, M)
	{
		cin >> ch;
		ul = ID(i, j); ur = ul + 1;
		dl = ID(i + 1, j); dr = dl + 1;
		if (ch == 'X' || ch == '\\')
		{
			a[ul][side]++; a[dr][side]++;
			if (getfather(ul) != getfather(dr))
				p[p[ul]] = p[dr];
		}
		if (ch == 'X' || ch == '/')
		{
			a[ur][side]++; a[dl][side]++;
			if (getfather(ur) != getfather(dl))
				p[p[ur]] = p[dl];
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	cin >> N >> M;
	n = (N + 1) * (M + 1);
	int i;
	REP(i, n)
	{
		p[i] = i;
	}
	MakeGraph(0);
	MakeGraph(1);
	REP(i, n)
		if (a[i][0] || a[i][1])
			sum[getfather(i)] += abs(a[i][0] - a[i][1]);
	int res = 0;
	REP(i, n)
		if ((a[i][0] || a[i][1]) && p[i] == i)
			res += sum[i] ? sum[i] / 2 : 1;
	cout << res << endl;
	return 0;
}
