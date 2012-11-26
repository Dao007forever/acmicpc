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

const double eps = 1e-8;
#define maxn 100 + 10
#define maxm 100 * maxn
const int inf = 0x3f3f3f3f;
struct Nod
{
	int b, nxt;
	int cap, cst;
	void init(int b, int nxt, int cap, int cst)
	{
		this->b = b;
		this->nxt = nxt;
		this->cap = cap;
		this->cst = cst;
	}
};
struct MinCost
{
	int E[maxn], n;
	Nod buf[maxm * 2]; int len;

	int p[maxn];
	void init(int n)
	{
		this->n = n;
		memset(E, 255, sizeof(E));
		len = 0;
	}
	void addCap(int a, int b, int cap, int cst)
	{
		buf[len].init(b, E[a], cap, cst); E[a] = len++;
		buf[len].init(a, E[b], 0, -cst); E[b] = len++;
	}
	bool spfa(int source, int sink)
	{
		static queue<int> Q;
		static int d[maxn];
		memset(d, 63, sizeof(d));
		memset(p, 255, sizeof(p));

		d[source] = 0;
		Q.push(source);
		int u, v;
		while (!Q.empty())
		{
			u = Q.front();
			Q.pop();
			for (int i = E[u]; i != -1; i = buf[i].nxt)
			{
				v = buf[i].b;
				if (buf[i].cap > 0 && d[u] + buf[i].cst < d[v])
				{
					d[v] = d[u] + buf[i].cst;
					p[v] = i;
					Q.push(v);
				}
			}
		}
		return d[sink] != inf;
	}
	int solve(int source, int sink)
	{
		int minCost = 0, maxFlow = 0;
		while (spfa(source, sink))
		{
			int neck = inf;
			for (int t = p[sink]; t != -1; t = p[buf[t ^ 1].b])
				neck = min(neck, buf[t].cap);
			maxFlow += neck;
			for (int t = p[sink]; t != -1; t = p[buf[t ^ 1].b])
			{
				buf[t].cap -= neck;
				buf[t ^ 1].cap += neck;
				minCost += buf[t].cst * neck;
			}
		}
		return minCost;
	}
} mic, mac;

int main()
{
	freopen("in", "r", stdin);
	int n, m;
	int cas = 1;
	while (scanf("%d%d", &n, &m) && (n || m))
	{
		printf("Problem %d: ", cas++);
		int source = 0, sink = n + m + 1;
		mic.init(n + m + 2);
		mac.init(n + m + 2);
		for (int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d", &x);
			mic.addCap(source, i, x, 0);
			mac.addCap(source, i, x, 0);
		}
		for (int i = 1; i <= m; i++)
		{
			int x;
			scanf("%d", &x);
			mic.addCap(n + i, sink, x, 0);
			mac.addCap(n + i, sink, x, 0);
		}
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			double x;
			scanf("%lf", &x);
			if (x != -1.0)
			{
				int tmp = (int)(x * 100 + 0.0005);
				mic.addCap(i, j + n, inf, tmp);
				mac.addCap(i, j + n, inf, -tmp);
			}
		}
		double ret1 = (double)mic.solve(source, sink) / 100;
		double ret2 = -(double)mac.solve(source, sink) / 100;
		printf("%.2lf to %.2lf\n", ret1, ret2);
	}
	return 0;
}
