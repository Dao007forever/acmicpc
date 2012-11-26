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

const int MAXN = 10000 + 10;
int N, M;
int p[MAXN];

int getfather(int x)
{
	if (p[x] != x) p[x] = getfather(p[x]);
	return p[x];
}

int main()
{
	freopen("a", "r", stdin);
	cin >> N >> M;
	if (N != M + 1)
	{
		cout << "NO" << endl;
	}
	else
	{
		int i;
		bool flag;
		FOR(i, 1, N)
			p[i] = i;
		flag = true;
		REP(i, M)
		{
			int a, b;
			cin >> a >> b;
			int fa = getfather(a), fb = getfather(b);
			if (fa == fb) flag = false;
			p[fa] = fb;
		}
		if (flag)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	return 0;
}
