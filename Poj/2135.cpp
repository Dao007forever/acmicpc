#include <set>
#include <map>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
#include <bitset>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000 + 10;
const int MAXM = 10000 + 10;
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
	int E[MAXN], n;
	Nod buf[MAXM * 4]; int len;

	int p[MAXN];
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
		static int d[MAXN];
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
} mc;

int N, M;

int main()
{
	freopen("a.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	mc.init(N + 2);
	int source = 0, sink = N + 1;
	for (int i = 1; i <= M; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		mc.addCap(a, b, 1, c);
		mc.addCap(b, a, 1, c);	
	}
	mc.addCap(source, 1, 2, 0);
	mc.addCap(N, sink, 2, 0);
	printf("%d\n", mc.solve(source, sink));
	return 0;
}
