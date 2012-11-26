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
struct Ins
{
	char dir[5];
	int len;
}P[MAXN * 10];
int N, M, cnt, K;
int num[MAXN][MAXN], sum1[MAXN][MAXN], sum2[MAXN][MAXN];
char Map[MAXN][MAXN];
char ans[MAXN];

void Prepare()
{
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= M; j++)
	{
		if (Map[i][j] == '#')
			num[i][j] = 1;
		else num[i][j] = 0;
		sum1[i][j] = sum1[i][j - 1] + num[i][j];
		sum2[i][j] = sum2[i - 1][j] + num[i][j];
	}
}

bool check(int x, int y)
{
	if (x <= 0 || x > N || y <= 0 || y > M) return false;
	return true;
}

bool dfs(int x, int y)
{
	int xx, yy;
	for (int i = 1; i <= K; i++)
	{
		if (P[i].dir[0] == 'N')
		{
			xx = x - P[i].len;
			yy = y;
			if (!check(xx, yy)) return false;
			if (sum2[x][y] - sum2[xx - 1][yy] != 0) return false;
		}
		if (P[i].dir[0] == 'S')
		{
			xx = x + P[i].len;
			yy = y;
			if (!check(xx, yy)) return false;
			if (sum2[xx][yy] - sum2[x - 1][y] != 0) return false;
		}
		if (P[i].dir[0] == 'E')
		{
			xx = x;
			yy = y + P[i].len;
			if (!check(xx, yy)) return false;
			if (sum1[xx][yy] - sum1[x][y - 1] != 0) return false;
		}
		if (P[i].dir[0] == 'W')
		{
			xx = x;
			yy = y - P[i].len;
			if (!check(xx, yy)) return false;
			if (sum1[x][y] - sum1[xx][yy - 1] != 0) return false;
		}
		x = xx;
		y = yy;
	}
	return true;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%s", Map[i] + 1);
	scanf("%d", &K);
	for (int i = 1; i <= K; i++)
		scanf("%s %d", P[i].dir, &P[i].len);

	Prepare();

	int cnt = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		if (Map[i][j] != '#' && Map[i][j] != '.')
		{
			bool flag = dfs(i, j);
			if (flag) ans[cnt++] = Map[i][j];
		}
	sort(ans, ans + cnt);
	if (cnt == 0) printf("no solution\n");
	else printf("%s\n", ans);
	return 0;
}
