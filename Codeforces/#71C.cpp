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
char s[MAXN];
int dp[MAXN], a[MAXN];
char t[15][15];

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", s);
	int n = strlen(s), m;
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%s", t[i]);
		a[i] = strlen(t[i]);
	}
	int i, j, k, r;
	for (i = r = 0; i < n; i++)
	{
		if (i) dp[i] = dp[i - 1] + 1;
		else dp[i] = 1;
		for (j = 0; j < m; j++)
		{
			if (a[j] <= i + 1)
			{
				for (k = 0; k < a[j]; k++)
				if (s[i - k] != t[j][a[j] - 1 - k])
					break;
				if (k >= a[j] && a[j] - 1 < dp[i])
					dp[i] = a[j] - 1;
			}
		}
		if (dp[i] > dp[r])
			r = i;
	}
	printf("%d %d\n", dp[r], r - dp[r] + 1);
	return 0;
}
