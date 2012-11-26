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
const int MAXM = 10000 + 10;
struct Edge
{
	int u, v, next;
}edge[MAXM * 4], edge2[MAXM * 4];
int n, m;
int num, Head[MAXN], num2, Head2[MAXN];
int deg[MAXN], p[MAXN], q[MAXN], ans[MAXN];

void addEdge(int u, int v)
{
	edge[num].u = u;
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void addEdge2(int u, int v)
{
	edge2[num2].u = u;
	edge2[num2].v = v;
	edge2[num2].next = Head2[u];
	Head2[u] = num2++;
}

void init()
{
	num = num2 = 0;
	memset(Head, -1, sizeof(Head));
	memset(Head2, -1, sizeof(Head2));
	memset(deg, 0, sizeof(deg));
	memset(q, 0, sizeof(q));
	memset(ans, 0, sizeof(ans));
}

int find(int x)
{
	if (p[x] != x) p[x] = find(p[x]);
	return p[x];
}

void Union(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x != y) p[x] = y;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		init();
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			p[i] = i;
		for (int i = 1; i <= m; i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			if (c == 0) Union(a, b);
			else if (c == 1)
			{
				addEdge(b, a);
			}
			else addEdge(a, b);
		}

		bool flag = true;
		for (int i = 0; i < num; i++)
			if (find(edge[i].u) == find(edge[i].v))
			{
				flag = false;
				break;
			}
		if (!flag)
		{
			printf("NO\n");
			continue;
		}

		for (int i = 0; i < num; i++)
		{
			int u = find(edge[i].u), v = find(edge[i].v);
			//cout << u << " " << v << endl;
			addEdge2(u, v);
			deg[v]++;
		}
		int nn = 0, cnt = 0;
		for (int i = 1; i <= n; i++)
			if (p[i] == i)
			{
				nn++;
				if (deg[i] == 0)
				{
					q[cnt++] = i;
				}
			}
		for (int i = 0; i < cnt; i++)
		{
			int u = q[i];
			for (int i = Head2[u]; i != -1; i = edge2[i].next)
			{
				if (ans[u] + 1 > ans[edge2[i].v])
					ans[edge2[i].v] = ans[u] + 1;
				deg[edge2[i].v]--;
				if (deg[edge2[i].v] == 0)
				{
					q[cnt++] = edge2[i].v;
				}
			}
		}
		if (cnt < nn) printf("NO\n");
		else
		{
			int ret = 0;
			for (int i = 0; i < cnt; i++)
				ret = max(ret, ans[q[i]]);
			printf("%d\n", ret);
		}
	}
	return 0;
}
