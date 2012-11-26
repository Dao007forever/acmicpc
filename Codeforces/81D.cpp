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

const int MAXM = 50;
const int MAXN = 1000 + 10;
int N, M;
int a[MAXN], res[MAXN];

int main()
{
	freopen("a", "r", stdin);
	cin >> N >> M;
	int i, j;
	FOR(i, 1, M)
	{
		cin >> a[i];
	}
	int ok = 1;
	FOR(i, 1, N)
	{
		ok = 0;
		FOR(j, 1, M)
		{
			if (a[j] && j != res[i - 1] && (i < N || j != res[1]))
			{
				if (i > 1)
				{
					if (j == res[1] || a[j] > a[ok])
						ok = j;
				}
				else
				{
					if (a[j] < a[ok] || !ok)
						ok = j;
				}
			}
		}
		if (!ok) break;
		a[ok]--;
		res[i] = ok;
	}
	if (!ok) cout << -1 << endl;
	else 
	{
		FOR(i, 1, N)
		{
			printf("%d", res[i]);
			if (i < N) printf(" ");
			else printf("\n");
		}
	}
	return 0;
}
