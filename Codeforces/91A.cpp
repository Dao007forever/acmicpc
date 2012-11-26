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

const int MAXN = 10000 + 10;
const int MAXM = 1000000 + 10;
int n, m;
char s1[MAXN], s2[MAXM];
int Next[MAXN][30], used[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%s%s", s1, s2);
	n = strlen(s1); m = strlen(s2);

	for (int i = 0; i < n; i++)
		used[s1[i]] = 1;
	for (int i = 0; i < m; i++)
	if (!used[s2[i]])
	{
		printf("-1\n");
		return 0;
	}

	for (int i = 0; i < 30; i++)
		Next[n][i] = -1;
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 0; j < 30; j++)
			Next[i][j] = Next[i + 1][j];
		Next[i][s1[i] - 'a'] = i;
	}

	int j = 0, res = 1;
	for (int i = 0; i < m; i++)
	{
		if (Next[j][s2[i] - 'a'] == -1)
		{
			res++;
			j = 0;
		}
		j = Next[j][s2[i] - 'a'] + 1;
	}
	printf("%d\n", res);
	return 0;
}
