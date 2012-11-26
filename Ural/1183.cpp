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

#define REP(i, n) for(i = 0; i < (n); ++i)
#define FOR(i, l, h) for(i = (l); i <= (h); ++i)
#define FORD(i, h, l) for(i = (h); i >= (l); --i)

const int MAXN = 100 + 10;
const int INF = 0x3f3f3f3f;
int N;
char s[MAXN];
int dp[MAXN][MAXN] = {0}, p[MAXN][MAXN] = {0};

void Print(int x, int y)
{
	if (x > y) return;
	if (x == y)
	{
		if (s[x] == '(' || s[x] == ')')
			printf("()");
		else printf("[]");
		return;
	}
	if (p[x][y] > 0)
	{
		Print(x, p[x][y]);
		Print(p[x][y] + 1, y);
	}
	else if (p[x][y] == -1)
	{
		printf("%c", s[x]);
		Print(x + 1, y - 1);
		printf("%c", s[y]);
	}
	else if (p[x][y] == -2)
	{
		if (s[x] == '(')
		{
			printf("(");
			Print(x + 1, y);
			printf(")");
		}
		else
		{
			printf("[");
			Print(x + 1, y);
			printf("]");
		}
	}
	else if (p[x][y] == -3)
	{
		if (s[x] == '(')
		{
			printf("(");
			Print(x, y - 1);
			printf(")");
		}
		else
		{
			printf("[");
			Print(x, y - 1);
			printf("]");
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", s + 1);
	N = strlen(s + 1);
	for (int i = 1; i <= N; i++)
		dp[i][i] = 1;
	for (int k = 1; k < N; k++)
	for (int i = 1; i <= N - k; i++)
	{
		int j = i + k;
		dp[i][j] = INF;
		for (int t = i; t < j; t++)
		if (dp[i][t] + dp[t + 1][j] < dp[i][j])
		{
			dp[i][j] = dp[i][t] + dp[t + 1][j];
			p[i][j] = t;
		}
		if ((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']'))
		{
			if (dp[i + 1][j - 1] < dp[i][j])
			{
				dp[i][j] = dp[i + 1][j - 1];
				p[i][j] = -1;
			}
		}
		if (s[i] == '(' || s[i] == '[')
		{
			if (dp[i + 1][j] + 1 < dp[i][j])
			{
				dp[i][j] = dp[i + 1][j] + 1;
				p[i][j] = -2;
			}
		}
		if (s[i] == ')' || s[i] == ']')
		{
			if (dp[i][j - 1] + 1 < dp[i][j])
			{
				dp[i][j] = dp[i][j - 1] + 1;
				p[i][j] = -3;
			}
		}
	}
	Print(1, N);
	printf("\n");
	return 0;
}
