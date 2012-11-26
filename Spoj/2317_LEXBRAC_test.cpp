#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
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

int n, k;
int dp[255][255];
int stack[255];

int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &k);
	dp[0][0] = 1;
	for (int j = 1; j <= n; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			if (i > 0) dp[i][j] += dp[i - 1][j - 1];
			if (i + 1 <= j - 1) dp[i][j] += dp[i + 1][j - 1] * 2;
		}
	}
	
	int top = 0, now = 0;
	for (int i = 1; i <= n; i++)
	{
		if (top > 0 && stack[top] == 0) top--;
		now += dp[top + 1][n - i];
printf("%d\n", now);
		if (now >= k)
		{
			stack[++top] = 1;
			now -= dp[top][n - i];
			printf("(");
			continue;
		}
		if (top > 0 && stack[top] == 1)
		{
			now += dp[top - 1][n - i];
			if (now >= k)
			{
				top--;
				now -= dp[top][n - i];
				printf(")");
				continue;
			}
		}
		now += dp[top + 1][n - i];
printf("%d\n", now);
		if (now >= k)
		{
			stack[++top] = 2;
			now -= dp[top][n - i];
			printf("[");
			continue;
		}
		if (top > 0 && stack[top] == 2)
		{
			now += dp[top - 1][n - i];
			if (now >= k)
			{
				top--;
				now -= dp[top][n - i];
				printf("]");
				continue;
			}
		}
	}
	printf("\n");
}
