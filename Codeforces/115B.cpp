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

const int MAXN = 155;
int n, m;
int L[MAXN], R[MAXN];
char g[MAXN][MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%s", g[i]);

	int max_n = 0;
	for (int i = 0; i < n; i++)
	{
		L[i] = m; R[i] = -1;
		for (int j = 0; j < m; j++)
		if (g[i][j] == 'W')
		{
			L[i] = min(L[i], j);
			R[i] = max(R[i], j);
		}
		if (R[i] != -1) max_n = max(max_n, i);
	}

	int res = 0, pos = 0;
	for (int i = 0; i <= max_n; i++)
	{
		if (i % 2 == 0)
		{
			res += max(0, R[i] - pos);
			pos = max(pos, R[i]);
			if (i + 1 < n)
			{
				res += max(0, R[i + 1] - pos);
				pos = max(pos, R[i + 1]);
			}
		}
		else
		{
			res += max(0, pos - L[i]);
			pos = min(pos, L[i]);
			if (i + 1 < n)
			{
				res += max(0, pos - L[i + 1]);
				pos = min(pos, L[i + 1]);
			}
		}
	}
	printf("%d\n", res + max_n);
	return 0;
}
