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

const int MAXN = 200000 + 10;
int N, N1, N2;
int a[MAXN], r[MAXN], res[MAXN];

bool cmp(int i, int j)
{
	if (a[i] != a[j] && N1 != N2)
	{
		if (N1 > N2)
			return a[i] < a[j];
		else return a[i] > a[j];
	}
	else return i < j;
}

int main()
{
	freopen("a", "r", stdin);
	cin >> N >> N1 >> N2;
	int i;
	REP(i, N)
	{
		cin >> a[i];
		r[i] = i;
	}
	sort(r, r + N, cmp);
	REP(i, N1)
	{
		res[r[i]] = 1;
	}
	REP(i, N)
	{
		if (res[i])
		{
			putchar('1');
			if (i != N) putchar(' ');
		}
		else 
		{
			putchar('2');
			if (i != N) putchar(' ');
		}
	}
	puts("");
	return 0;
}
