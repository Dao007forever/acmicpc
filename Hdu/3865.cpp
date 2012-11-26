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

const int MAXN = 35;
const int MAXM = 111111;
const int inf = 1000000005;
int cost[25][25][5];
int dp[25][25][3];
int g[25][25];
int cx[MAXN], cy[MAXN], mk[MAXN], Row[MAXN], Col[MAXN];
int N, M, P, Q;
struct Edge
{
	int v, next;
}edge[MAXM];
int num;
int Head[MAXN];

void add(int u, int v)
{
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int path(int u)
{
        for (int i = Head[u]; i != -1; i = edge[i].next)
        {
			int v = edge[i].v;
                if ((!mk[v]))
                {
                        mk[v] = 1;
                        if (!cy[v] || path(cy[v]))
                        {
                                cx[u] = v;
                                cy[v] = u;
                                return 1;
                        }
                }
        }
        return 0;
}

int MaxMatch()
{
        int res = 0;
        memset(cx, 0, sizeof(cx));
        memset(cy, 0, sizeof(cy));
        for (int i = 1; i <= M; i++)
        {
                if (!cx[i])
                {
                        memset(mk, 0, sizeof(mk));
                        res += path(i);
                }
        }
        return res;
}

void cal_val(int g[25][25], int x, int y)
{
	memset(Row, 0, sizeof(Row));
	memset(Col, 0, sizeof(Col));
	memset(Head, -1, sizeof(Head));
	num = 0;
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= M; j++)
		if (g[i][j])
		{
			add(i, j);
			Row[i]++;
			Col[j]++;
		}
	cost[x][y][1] = cost[x][y][2] = 0;
	for (int i = 1; i <= M; i++)
	{
		if (Row[i]) cost[x][y][1] += P;
		if (Col[i]) cost[x][y][2] += P;
	}
	cost[x][y][3] = cost[x][y][4] = MaxMatch() * P + Q;
}

void Min(int &a, int b)
{
	if (b < a) a = b;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d%d%d", &N, &M, &P, &Q) != EOF)
	{
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
			{
				for (int k = 1; k <= M; k++)
					for (int h = 1; h <= M; h++)
						scanf("%d", &g[k][h]);
				cal_val(g, i, j);
			}
		for (int i = 0; i <= N; i++)
			for (int j = 0; j <= N; j++)
				for (int k = 1; k <= 2; k++)
					dp[i][j][k] = inf;
		dp[1][1][1] = min(cost[1][1][1], cost[1][1][4]);
		dp[1][1][2] = min(cost[1][1][2], cost[1][1][3]);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
			{
				if (i == 1 && j == 1) continue;
				Min(dp[i][j][1], dp[i - 1][j][1] + cost[i][j][1]);
				Min(dp[i][j][1], dp[i - 1][j][1] + cost[i][j][4] + Q);
				Min(dp[i][j][1], dp[i - 1][j][2] + cost[i][j][1] + Q);
				Min(dp[i][j][1], dp[i - 1][j][2] + cost[i][j][4] + Q + Q);

				Min(dp[i][j][2], dp[i - 1][j][1] + cost[i][j][2] + Q);
				Min(dp[i][j][2], dp[i - 1][j][1] + cost[i][j][3]);
				Min(dp[i][j][2], dp[i - 1][j][2] + cost[i][j][2] + Q + Q);
				Min(dp[i][j][2], dp[i - 1][j][2] + cost[i][j][3] + Q);

				Min(dp[i][j][1], dp[i][j - 1][1] + cost[i][j][1] + Q + Q);
				Min(dp[i][j][1], dp[i][j - 1][1] + cost[i][j][4] + Q);
				Min(dp[i][j][1], dp[i][j - 1][2] + cost[i][j][1] + Q);
				Min(dp[i][j][1], dp[i][j - 1][2] + cost[i][j][4]);

				Min(dp[i][j][2], dp[i][j - 1][1] + cost[i][j][2] + Q);
				Min(dp[i][j][2], dp[i][j - 1][1] + cost[i][j][3] + Q + Q);
				Min(dp[i][j][2], dp[i][j - 1][2] + cost[i][j][2]);
				Min(dp[i][j][2], dp[i][j - 1][2] + cost[i][j][3] + Q);
			}
		int ans = min(dp[N][N][1], dp[N][N][2]);
		cout << ans << endl;
	}
	return 0;
}
