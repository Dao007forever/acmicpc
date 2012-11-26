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

const int MAXN = 1000 + 10;
const double eps = 1e-6;
double dp[MAXN][MAXN], p[MAXN][MAXN][3];
int N, M;

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				for (int k = 0; k < 3; k++)
					scanf("%lf", &p[i][j][k]);

		memset(dp, 0, sizeof(dp));
		for (int i = N; i >= 1; i--)
			for (int j = M; j >= 1; j--)
			{
				if (i == N && j == M) continue;
				if (fabs(p[i][j][0] - 1) < eps) continue;
				dp[i][j] = (p[i][j][1] * dp[i][j + 1] + p[i][j][2] * dp[i + 1][j] + 1) / (1 - p[i][j][0]);
			}
		printf("%.3lf\n", dp[1][1] * 2);
	}
	return 0;
}
