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

char s[26];
int edge[26][26];
int N;
int res, c[26];
int vis[26];

void Greedy()
{
	for (int i = 0; i < N; i++)
	{
		memset(vis, 0, sizeof(vis));
		for (int k = 0; k < N; k++)
		{
			if (edge[i][k] && c[k] != -1)
			{
				vis[c[k]] = 1;
			}
		}
		int k;
		for (k = 0; k < N; k++)
		{
			if (!vis[k]) break;
		}
		c[i] = k;
	}
	for (int i = 0; i < N; i++)
	{
		if (c[i] > res)
			res = c[i];
	}
	res++;
}

int main()
{
	freopen("a.txt", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		memset(edge, 0, sizeof(edge));
		for (int i = 0; i < N; i++)
			c[i] = -1;
		res = 0;
		for (int i = 0; i < N; i++)
		{
			scanf("%s", s);
			int m = strlen(s) - 2;
			for (int k = 0; k < m; k++)
			{
				edge[i][s[k + 2] - 'A'] = 1;
				edge[s[k + 2] - 'A'][i] = 1;
			}
		}
		Greedy();
		if (res != 1) printf("%d channels needed.\n", res);
		else printf("%d channel needed.\n", res);
	}
	return 0;
}
