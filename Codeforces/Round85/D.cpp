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

const int MAXN = 100000 + 10;
int n;
int pos[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		int cnt = 0;
		scanf("%d%d", &x, &y);
		for (int j = 1; j <= (int)sqrt(x); j++)
		{
			if (x % j == 0)
			{
				if (pos[j] < i - y) cnt++;
				pos[j] = i;
				if (pos[x / j] < i - y) cnt++;
				pos[x / j] = i;
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}
