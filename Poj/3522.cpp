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

const int MAXN = 100 + 10;
const int MAXM = 10000 + 10;
const int inf = 0x3f3f3f3f;
struct Edge
{
	int u, v, w;
	bool operator<(Edge it) const
	{
		return w < it.w;
	}
}edge[MAXM];
int N, M;
int p[MAXN], rank[MAXN], ans, num, temp;

void init()
{
	for (int i = 1; i <= N; i++)
		p[i] = i;
	memset(rank, 0, sizeof(rank));
}

int getfather(int x)
{
	if (x != p[x])
		p[x] = getfather(p[x]);
	return p[x];
}

void Union(int a, int b)
{
	int pa = getfather(a), pb = getfather(b);
	if (rank[pa] > rank[pb]) p[pb] = pa;
	else if (rank[pa] < rank[pb]) p[pa] = pb;
	else
	{
		p[pa] = pb;
		rank[pb]++;
	}
}

void Kruskal()
{
	ans = inf;
	for (int i = 0; i < M - N + 2; i++)
	{
		init();
		temp = -1;
		num = 0;
		for (int j = i; j < M; j++)
		{
			if (getfather(edge[j].u) != getfather(edge[j].v))
			{
				num++;
				Union(edge[j].u, edge[j].v);
				if (num == N - 1)
				{
					temp = edge[j].w - edge[i].w;
					break;
				}
			}
		}
		if (temp == -1) break;
		if (temp != -1 && temp < ans) ans = temp;
	}
	if (ans >= inf) printf("-1\n");
	else printf("%d\n", ans);
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M), N || M)
	{
		for (int i = 0; i < M; i++)
			scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
		sort(edge, edge + M);
		Kruskal();
	}
	return 0;
}
