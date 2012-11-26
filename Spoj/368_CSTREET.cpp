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
const int MAXM = 300000 + 10;
struct Edge
{
	int u, v, w;
}edge[MAXM];
int N, M, P;
int p[MAXN], rank[MAXN];

int getfather(int x)
{
	if (x != p[x])
		p[x] = getfather(p[x]);
	return p[x];
}

void Union(int x, int y)
{
	x = getfather(x); y = getfather(y);
	if (rank[x] > rank[y])
	{
		p[y] = x;
	}
	else
	{
		p[x] = y;
		if (rank[x] == rank[y]) rank[y]++;
	}
}

int Kruskal()
{
	int res = 0, num = 0;
	int u, v;
	for (int i = 1; i <= N; i++)
	{
		p[i] = i;
		rank[i] = 0;
	}
	for (int i = 0; i < M; i++)
	{
		u = edge[i].u;
		v = edge[i].v;
		if (getfather(u) != getfather(v))
		{
			res += edge[i].w;
			num++;
			Union(u, v);
		}
		if (num > N - 1) break;
	}
	return res * P;
}

bool cmp(Edge a, Edge b)
{
	return a.w < b.w;
}

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d%d", &P, &N, &M);
		for (int i = 0; i < M; i++)
			scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
		sort(edge, edge + M, cmp);
		cout << Kruskal() << endl;
	}
	return 0;
}
