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
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

#define maxn 200 + 10
#define maxm 40000 + 10
#define th(x) this->x = x
const int inf = 0x3f3f3f3f;
struct Nod
{
	int b, next;
	int cap, flow, low;
	void init(int b, int low, int up, int next)
	{
		th(b);
		th(low);
		cap = up - low;
		th(next);
	}
};
struct BoundFlow
{
	int E[maxn], n;
	bool b[maxn];
	int h[maxn], vh[maxn], source, sink;
	Nod buf[maxm]; int len;
	int lowSumIn[maxn], lowSumOut[maxn];
	void init(int n)
	{
		this->n = n;
		len = 0;
		memset(b, 0, sizeof(b));
		memset(E, 255, sizeof(E));
		memset(lowSumIn, 0, sizeof(lowSumIn));
		memset(lowSumOut, 0, sizeof(lowSumOut));
	}
	void addCap(int i, int j, int low, int up)
	{
		buf[len].init(j, low, up, E[i]);
		E[i] = len++;
		buf[len].init(i, 0, 0, E[j]);
		E[j] = len++;
		lowSumIn[j] += low;
		lowSumOut[i] += low;
	}
	void popCap(int i, int j)
	{
		E[j] = buf[E[j]].next;
		E[i] = buf[E[i]].next;
		len -= 2;
	}
	int sap(const int idx, const int maxCap)
	{
		if (idx == sink)
			return maxCap;
		int l = maxCap, d, minH = n;
		for (int i = E[idx]; i != -1; i = buf[i].next)
		{
			Nod & nod = buf[i];
			if (nod.cap - nod.flow > 0)
			{
				if (h[idx] == h[nod.b] + 1)
				{
					d = sap(nod.b, min(l, nod.cap - nod.flow));
					nod.flow += d;
					buf[i ^ 1].flow -= d;
					l -= d;
					if (h[source] == n || l == 0) return maxCap - l;
				}
				minH = min(minH, h[nod.b] + 1);
			}
		}
		if (l == maxCap)
		{
			vh[h[idx]]--;
			vh[minH]++;
			if (vh[h[idx]] == 0)
				h[source] = n;
			h[idx] = minH;
		}
		return maxCap - l;
	}
	int solveSAP(int source, int sink)
	{
		if (source == sink) return inf;
		th(source); th(sink);
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		int ans = 0;
		while (h[source] != n)
			ans += sap(source, inf);
		return ans;
	}
	int solve(int source, int sink)
	{
		int total = 0;
		for (int i = 0; i < n; i++)
		{
			addCap(i, n + 1, 0, lowSumOut[i]);
			addCap(n, i, 0, lowSumIn[i]);
			total += lowSumIn[i];
		}
		n += 2;
		addCap(source, sink, 0, inf);
		for (int i = 0; i < len; i++)
			buf[i].flow = 0;
		int ans = solveSAP(n - 2, n - 1);
		popCap(sink, source);
		n -= 2;
		for (int i = n - 1; i >= 0; i--)
		{
			popCap(n, i);
			popCap(i, n + 1);
		}
		if (total != ans) return 0;
		else return 1;
	}
	void print(int source, int sink)
	{
		solveSAP(source, sink);
		for (int i = 0; i < len; i++)
		{
			buf[i].flow += buf[i].low;
			if (buf[i].flow > 0) printf("%d ", buf[i].flow);
		}
	}
};
//sgu 176，求最小流，枚举源点到汇点的流量下界
BoundFlow bf;

int main()
{
	freopen("a.txt", "r", stdin);
	int N, M;
	scanf("%d%d", &N, &M);
	bf.init(N);
	for (int i = 1; i <= M; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		if (d == 0) bf.addCap(a, b, 0, c);
		else bf.addCap(a, b, c, c);
	}
	if (!bf.solve(1, N))
	{
		printf("Impossible\n");
	}
	else
	{
		int Left = -1, Right = 1000000, Mid;
		bf.init(N + 2);
		while (Left <= Right)
		{
			Mid = (Left + Right) / 2;
			bf.addCap(1, N, Mid, inf);
			if (bf.solve(0, N + 1)) Right = Mid - 1;
			else Left = Mid + 1;
		}
		printf("%d\n", Right + 1);
		bf.print(0, N + 1);
	}
	return 0;
}
