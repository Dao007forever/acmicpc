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

const int MAXN = 100 + 10;
struct Lap
{
	int s, r, h, c;
}P[MAXN];
int N;
int vis[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d%d%d%d", &P[i].s, &P[i].r, &P[i].h, &P[i].c);
	}
	memset(vis, 1, sizeof(vis));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (i != j && P[i].s < P[j].s && P[i].r < P[j].r && P[i].h < P[j].h)
			{
				vis[i] = 0;
				break;
			}
		}
	}
	int k, Min = 100000000;
	for (int i = 1; i <= N; i++)
	if (vis[i])
	{
		if (P[i].c < Min)
		{
			Min = P[i].c;
			k = i;
		}
	}
	printf("%d\n", k);
	return 0;
}
