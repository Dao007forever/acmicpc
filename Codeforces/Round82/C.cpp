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

struct Type
{
	int a, b, c, d;
}P[15];
int N, M, c0, d0;
int dp[1005];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d%d%d", &N, &M, &c0, &d0);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d%d%d%d", &P[i].a, &P[i].b, &P[i].c, &P[i].d);
	}
	P[0].a = 0; P[0].b = 0; P[0].c = c0; P[0].d = d0;

	memset(dp, 0, sizeof(dp));
	for (int i = 0; i <= M; i++)
	{
		for (int j = N; j >= 0; j--)
		{
			for (int k = 1; k * P[i].c <= j && k * P[i].b <= P[i].a; k++)
			{
				if (dp[j - k * P[i].c] + k * P[i].d > dp[j])
					dp[j] = dp[j - k * P[i].c] + k * P[i].d;
			}
		}
	}
	printf("%d\n", dp[N]);
	return 0;
}
