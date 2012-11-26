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

const int MAXN = 100000 + 10;
int N, top, tot;
int a[MAXN], pre[MAXN], dp[MAXN], pos[MAXN], res[MAXN], vis[MAXN];
void Print(int idx)
{
	if (pre[idx] != 0)
		Print(pre[idx]);
	res[++tot] = a[idx];
}

int main()
{
//	freopen("a", "r", stdin);
	memset(pre, 0, sizeof(pre));
	memset(pos, 0, sizeof(pos));
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
		dp[i] = 100005;
	}
	pre[1] = 0;
	dp[1] = 1;
	pos[a[1]] = 1;
	for (int i = 2; i <= N; i++)
	{
		if (!pos[a[i]])
		{
			dp[i] = dp[i - 1] + 1;
			pre[i] = i - 1;
			pos[a[i]] = i;
		}
		else
		{
			int j = pos[a[i]];
			if (dp[j] < dp[i - 1] + 1)
			{
				dp[i] = dp[j];
				pre[i] = j;
			}
			else 
			{
				dp[i] = dp[i - 1] + 1;
				pre[i] = i - 1;
			}
		}
	}
	Print(N);
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= tot; i++)
	{
		if (!vis[res[i]])
		{
			printf("%d ", res[i]);
			vis[res[i]] = 1;
		}
	}
	return 0;
}
