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

const int MAXN = 111;
int N, S;
int dis[MAXN][MAXN];

int main()
{
	freopen("a", "r", stdin);
	int cas = 0;
	while (scanf("%d", &N) && N)
	{
		printf("Case %d: ", ++cas);
		memset(dis, -1, sizeof(dis));
		for (int i = 1; i <= N; i++)
			dis[i][i] = 0;
		scanf("%d", &S);
		int p, q;
		while (scanf("%d%d", &p, &q))
		{
			if (p == 0 && q == 0) break;
			dis[p][q] = 1;
		}

		for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			if (dis[i][k] != -1)
			{
				for (int j = 1; j <= N; j++)
				if (dis[k][j] != -1)
				{
					dis[i][j] = max(dis[i][j], dis[i][k] + dis[k][j]);
				}
			}
		int Max = 0, ans;
		for (int i = 1; i <= N; i++)
		if (dis[S][i] > Max)
		{
			Max = dis[S][i];
			ans = i;
		}
		printf("The longest path from %d has length %d, finishing at %d.\n", S, Max, ans);
		puts("");
	}
	return 0;
}
