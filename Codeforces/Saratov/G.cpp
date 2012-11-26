#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Team
{
	int a[5], b[5];
	int d[222];
	int num;
	char sol[222][22];
}T[222];
struct Card
{
	char name[22];
	int c, vis;
}C[222];
int n, t, m;
int now, idx;
int que[1111111];
bool end;

int main()
{
	freopen("in", "r", stdin);
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &t);
	for (int i = 1; i <= n; i++)
		scanf("%d%d%d%d", &T[i].a[1], &T[i].b[1], &T[i].a[2], &T[i].b[2]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
		scanf("%s%d", C[i].name, &C[i].c);

	int l = 1, r = m;
	for (int i = 1; i <= m; i++)
		que[i] = i;
	for (int now = 1; l <= r; now++)
	{
		if (now == 2 * n + 1) now = 1;
		int time = t;
		for (; l <= r && time; )
		{
			int k = que[l], tmp;
			l++;
			if (now <= n) tmp = max(1, C[k].c - (T[now].a[1] + T[now].b[2]) - T[now].d[k]);
			else tmp = max(1, C[k].c - (T[now - n].a[2] + T[now - n].b[1]) - T[now - n].d[k]);
			int idx;
			if (now > n) idx = now - n;
			else idx = now;
			if (tmp <= time)
			{
				strcpy(T[idx].sol[T[idx].num++], C[k].name);
				time -= tmp;
			}
			else
			{
				T[idx].d[k] += time;
				que[++r] = k;
				break;
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		printf("%d", T[i].num);
		for (int j = 0; j < T[i].num; j++)
			printf(" %s", T[i].sol[j]);
		puts("");
	}
	return 0;
}
