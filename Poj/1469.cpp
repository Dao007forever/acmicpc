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

const int MAXN = 300 + 10;
int T, P, N;
int course[MAXN][MAXN], used[MAXN], match[MAXN];

bool DFS(int k)
{
	int i, temp;
	for (int i = 1; i <= N; i++)
	{
		if (course[k][i] && !used[i])
		{
			used[i] = 1;
			temp = match[i];
			match[i] = k;
			if (temp == -1 || DFS(temp))
				return 1;
			match[i] = temp;
		}
	}
	return 0;
}

int MaxMatch()
{
	int MatchNum = 0;
	memset(match, -1, sizeof(match));
	for (int i = 1; i <= P; i++)
	{
		memset(used, 0, sizeof(used));
		if (DFS(i)) MatchNum++;
		if (MatchNum == P) break;
	}
	return MatchNum;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &P, &N);
		memset(course, 0, sizeof(course));
		for (int i = 1; i <= P; i++)
		{
			int num;
			scanf("%d", &num);
			for (int j = 1; j <= num; j++)
			{
				int t;
				scanf("%d", &t);
				course[i][t] = 1;
			}
		}
		if (MaxMatch() == P) printf("YES\n");
		else printf("NO\n");
	}
}
