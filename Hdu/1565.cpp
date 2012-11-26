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

const int MAXN = 500;
const int inf = 0x3f3f3f3f;

int N;
int a[MAXN][MAXN];
struct SAP
{
	int cap[MAXN][MAXN], flow[MAXN][MAXN];
	int n;
	int h[MAXN], vh[MAXN], source, sink;

	void init(int n)
	{
		this->n = n;
		memset(cap, 0, sizeof(cap));
	}

	void addCap(int i, int j, int val)
	{
		cap[i][j] += val;
	}

	int sap(const int idx, const int maxCap)
	{
		if (idx == sink)
			return maxCap;
		int l = maxCap, d, minH = n;
		for (int i = 0; i < n; i++)
		{
			if (cap[idx][i] - flow[idx][i] > 0)
			{
				if (h[idx] == h[i] + 1)
				{
					d = sap(i, min(l, cap[idx][i] - flow[idx][i]));
					flow[idx][i] += d;
					flow[i][idx] -= d;
					l -= d;
					if (h[source] == n || l == 0) return maxCap - l;
				}
				minH = min(minH, h[i] + 1);
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
		this->sink = sink;
		this->source = source;
		memset(flow, 0, sizeof(flow));
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		int ans = 0;
		while (h[source] != n)
			ans += sap(source, inf);
		return ans;
	}
};

SAP sap;

int ID(int i, int j)
{
	return i * N + j;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) != EOF)
	{
		int Sum = 0;
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &a[i][j]);
			Sum += a[i][j];
		}

		sap.init(N * N + 2);
		int source = N * N, sink = N * N + 1;
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (!((i + j) & 1))
			{
				sap.addCap(source, ID(i, j), a[i][j]);
				if (i - 1 >= 0)
					sap.addCap(ID(i, j), ID(i - 1, j), inf);
				if (i + 1 < N)
					sap.addCap(ID(i, j), ID(i + 1, j), inf);
				if (j - 1 >= 0)
					sap.addCap(ID(i, j), ID(i, j - 1), inf);
				if (j + 1 < N)
					sap.addCap(ID(i, j), ID(i, j + 1), inf);
			}
			else sap.addCap(ID(i, j), sink, a[i][j]);
		}
		printf("%d\n", Sum - sap.solve(source, sink));
	}
	return 0;
}
