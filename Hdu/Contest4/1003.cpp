#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 2147483647;
int N, M, K;
int feel[33][33], vis[33][33];
struct Time
{
	int h, m, q, id;
	int ansi, ansj, ans;
}t[55];

bool cmp(const Time &a, const Time &b)
{
	if (a.h == b.h) return a.m < b.m;
	return a.h < b.h;
}

bool check(int i, int j, int x)
{
	if (j + x - 1 > N) return false;
	for (int k = j; k <= j + x - 1; k++)
		if (vis[i][k]) return false;
	return true;
}

void find(int x, int idx)
{
	int maxi, maxj, maxii, maxjj, flag = false, Max = -inf, Max2 = -inf;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		if (!vis[i][j])
		{
			if (feel[i][j] > Max)
			{
				Max = feel[i][j];
				maxi = i, maxj = j;
			}
			if (check(i, j, x) && feel[i][j] > Max2)
			{
				Max2 = feel[i][j];
				maxii = i, maxjj = j;
				flag = true;
			}
		}
	if (flag) 
	{
		//printf("%d %d\n", maxii, maxjj);
		t[idx].ans = 1;
		t[idx].ansi = maxii;
		t[idx].ansj = maxjj;
		for (int j = maxjj; j <= maxjj + x - 1; j++)
			vis[maxii][j] = true;
	}
	else if (Max > -inf) 
	{
		//printf("%d %d\n", maxi, maxj);
		t[idx].ans = 1;
		t[idx].ansi = maxi;
		t[idx].ansj = maxj;
		vis[maxi][maxj] = true;
	}else t[idx].ans = -1;
}

bool cmp2(const Time &a, const Time &b)
{
	return a.id < b.id;
}

void output()
{
	for (int i = 0; i < K; i++)
		if (t[i].ans == 1) printf("%d %d\n", t[i].ansi, t[i].ansj);
		else printf("-1\n");
}

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d%d%d", &N, &M, &K) != EOF)
	{
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				scanf("%d", &feel[i][j]);

		for (int k = 0; k < K; k++)
		{
			scanf("%d:%d %d", &t[k].h, &t[k].m, &t[k].q);
			t[k].id = k;
		}
		sort(t, t + K, cmp);

		for (int k = 0; k < K; k++)
		{
			find(t[k].q, k);
		}
		sort(t, t + K, cmp2);
		output();
	}
	return 0;
}
