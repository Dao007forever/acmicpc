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

const int MAXN = 20;
const int MAX = 65536;
int T, N;
struct Course
{
	char name[105];
	int D, C;
}course[MAXN];
struct Node
{
	int cost, pre, reduced;
}dp[MAX];
bool vis[MAX];

void Print(int status)
{
	int curjob = dp[status].pre ^ status;
	int t = 0;
	curjob >>= 1;
	while (curjob)
	{
		t++;
		curjob >>= 1;
	}
	if (dp[status].pre != 0)
	{
		int preday = dp[status].cost - course[t].C;
		Print(dp[status].pre);
	}
	printf("%s\n", course[t].name);
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		int upper = 1 << N;
		for (int i = 0; i < N; i++)
		{
			scanf("%s%d%d", course[i].name, &course[i].D, &course[i].C);
		}
		memset(vis, 0, sizeof(vis));

		dp[0].cost = 0;
		dp[0].pre = -1;
		dp[0].reduced = 0;
		vis[0] = true;

		for (int j = 0; j < upper - 1; j++)
		{
			for (int i = 0; i < N; i++)
			{
				int cur = 1 << i;
				if ((cur & j) == 0)
				{
					int temp = cur | j;
					int day = dp[j].cost + course[i].C;
					dp[temp].cost = day;
					int reduce = day - course[i].D;
					if (reduce < 0) reduce = 0;
					reduce += dp[j].reduced;
					if (vis[temp])
					{
						if (reduce < dp[temp].reduced)
						{
							dp[temp].reduced = reduce;
							dp[temp].pre = j;
						}
					}
					else if (!vis[temp])
					{
						vis[temp] = true;
						dp[temp].reduced = reduce;
						dp[temp].pre = j;
					}
				}
			}
		}
		printf("%d\n", dp[upper - 1].reduced);
		Print(upper - 1);
	}
	return 0;
}
