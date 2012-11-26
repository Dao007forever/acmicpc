#include <set>
#include <map>
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

#define maxn 1000 + 10
#define maxm 10 * maxn
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
} mc;

int N;

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		int source = 0, sink = N + 1;
		mc.init(N + 2);
		for (int i = 1; i <= N; i++)
		{
			int x;
			scanf("%d", &x);
			mc.addCap(source, i, x, 0);
			mc.addCap(i, sink, 1, 0);
		}
		for (int i = 1; i <= N; i++)
		{
			if (i == 1)
			{
				mc.addCap(i, i + 1, inf, 1);
				mc.addCap(i, N, inf, 1);
			}
			else if (i == N)
			{
				mc.addCap(i, i - 1, inf, 1);
				mc.addCap(N, 1, inf, 1);
			}
			else
			{
				mc.addCap(i, i + 1, inf, 1);
				mc.addCap(i, i - 1, inf, 1);
			}
		}
		cout << mc.solve(source, sink) << endl;
	}
	return 0;
}
