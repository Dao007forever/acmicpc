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

#define th(x) this->x = x
const int MAXN = 3000;
const int MAXM = 100 * MAXN;
const int inf = 0x3f3f3f3f;
int N, M, K;
int a[100][100];
bool b[100][100];

struct Nod
{
	int b, next;
	int cap, flow;
	void init(int b, int cap, int next)
	{
		th(b);
		th(cap);
		th(next);
	}
};
struct SAP
{
	int E[MAXN], n;
	int h[MAXN], vh[MAXN], source, sink;
	Nod buf[MAXM]; int len;

	void init(int n)
	{
		this->n = n;
		len = 0;
		memset(E, 255, sizeof(E));
	}

	void addCap(int i, int j, int cap1, int cap2 = 0)
	{
		buf[len].init(j, cap1, E[i]);
		E[i] = len++;
		buf[len].init(i, cap2, E[j]);
		E[j] = len++;
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

	int solve(int source, int sink)
	{
		if (source == sink) return inf;
		th(source);
		th(sink);
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		for (int i = 0; i < len; i++)
			buf[i].flow = 0;
		int ans = 0;
		while (h[source] != n)
			ans += sap(source, inf);
		return ans;
	}
};

int ID(int i, int j)
{
	return i * M + j;
}

SAP sap;

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d%d", &N, &M, &K) != EOF)
	{
		memset(b, 0, sizeof(b));
		int Sum = 0;
		for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &a[i][j]);
			Sum += a[i][j];
		}
		for (int i = 1; i <= K; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			x--; y--;
			b[x][y] = true;
		}

		sap.init(N * M + 2);
		int source = N * M, sink = N * M + 1;
		for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			if (!((i + j) & 1))
			{
				if (b[i][j])
					sap.addCap(source, ID(i, j), inf);
				else sap.addCap(source, ID(i, j), a[i][j]);
				if (i - 1 >= 0)
					sap.addCap(ID(i, j), ID(i - 1, j), 2 * (a[i][j] & a[i - 1][j]));
				if (i + 1 < N)
					sap.addCap(ID(i, j), ID(i + 1, j), 2 * (a[i][j] & a[i + 1][j]));
				if (j - 1 >= 0)
					sap.addCap(ID(i, j), ID(i, j - 1), 2 * (a[i][j] & a[i][j - 1]));
				if (j + 1 < M)
					sap.addCap(ID(i, j), ID(i, j + 1), 2 * (a[i][j] & a[i][j + 1]));
			}
			else
			{
				if (b[i][j])
					sap.addCap(ID(i, j), sink, inf);
				else sap.addCap(ID(i, j), sink, a[i][j]);
			}
		}
		printf("%d\n", Sum - sap.solve(source, sink));
	}
	return 0;
}
