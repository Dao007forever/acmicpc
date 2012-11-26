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

#define maxn 410
#define maxm 4*maxn
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

map<int, int> Map;
int n, k;
int A[maxn], B[maxn], W[maxn];

int main()
{
//	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		Map.clear();

		scanf("%d%d", &n, &k);
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d%d", &A[i], &B[i], &W[i]);
			Map[A[i]];
			Map[B[i]];
		}
		int idx = 0;
		for (map<int, int>::iterator it = Map.begin(); it != Map.end(); it++)
		{
			it->second = idx++;
		}
		int N = Map.size();
		mc.init(N + 1);
		int source = N;
		mc.addCap(source, 0, k, 0);
		for (int i = 0; i < N - 1; i++)
			mc.addCap(i, i + 1, k, 0);
		for (int i = 0; i < n; i++)
		{
			mc.addCap(Map[A[i]], Map[B[i]], 1, -W[i]);
			//cout << Map[A[i]] << " " << Map[B[i]] << " " << W[i] << endl;
		}
		cout << -mc.solve(source, N - 1) << endl;
	}
	return 0;
}
