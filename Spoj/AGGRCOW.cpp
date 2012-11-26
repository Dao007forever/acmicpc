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

const int MAXN = 100000 + 10;
int T, N, M;
int a[MAXN];

bool Check(int limit)
{
	int r = a[1] + limit, i = 1, k = 1;
	while (i <= N)
	{
		for (; i < N && a[i + 1] <= r; i++);
		i++;
		r = a[i] + limit;
		k++;
		if (k > M) return false;
	}
	return true;
}

int main()
{
	freopen("a", "r", stdin);
	cin >> T;
	while (T--)
	{
		cin >> N >> M;
		int i;
		FOR(i, 1, N)
		{
			cin >> a[i];
		}
		sort(a + 1, a + N + 1);
		int Left = 0, Right = 1000000000;
		while (Left <= Right)
		{
			int Mid = (Left + Right) >> 1;
			if (!Check(Mid)) Left = Mid + 1;
			else Right = Mid - 1;
		}
		cout << Left << endl;
	}
	return 0;
}
