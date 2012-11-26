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

const int MAXN = 200 + 10;
const int Inf = 0x3f3f3f3f;
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
		if (source == sink) return Inf;
		this->source = source;
		this->sink = sink;
		memset(flow, 0, sizeof(flow));
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		int ans = 0;
		while (h[source] != n)
			ans += sap(source, Inf);
		return ans;
	}
};

SAP sap;
int N, M;

int main()
{
//	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &N, &M);
		sap.init(2 * N);
		for (int i = 0; i < N; i++)
			sap.cap[i][i + N] = 1;
		for (int i = 0; i < M; i++)
		{
			int a, b;
			scanf(" (%d,%d)", &a, &b);
			sap.cap[b + N][a] = sap.cap[a + N][b] = Inf;
		}
		int res = Inf;
		for (int i = 1; i < N; i++)
		{
			res = min(res, sap.solve(0 + N, i));
		}
		if (res == Inf) res = N;
		printf("%d\n", res);
	}
	return 0;
}
