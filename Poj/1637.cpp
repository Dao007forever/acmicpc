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
const int MAXN = 222;
const int MAXM = 10 * MAXN;
const int inf = 0x3f3f3f3f;
int N, M;
int outdeg[MAXN], indeg[MAXN];
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
}sap;
int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		memset(outdeg, 0, sizeof(outdeg));
		memset(indeg, 0, sizeof(indeg));
		scanf("%d%d", &N, &M);
		int source = 0, sink = N + 1;
		sap.init(N + 2);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			char op[5];
			scanf("%d%d%d", &u, &v, &w);
			outdeg[u]++;
			indeg[v]++;
			if (!w) sap.addCap(u, v, 1);
		}
		bool flag = false;
		for (int i = 1; i <= N; i++)
		{
			if (abs(outdeg[i] - indeg[i]) & 1)
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			puts("impossible");
			continue;
		}
		int sum = 0;
		for (int i = 1; i <= N; i++)
		{
			int x = (outdeg[i] - indeg[i]) / 2;
			if (x > 0)
			{
				sap.addCap(source, i, x);
				sum += x;
			}
			else sap.addCap(i, sink, -x);
		}
		int res = sap.solve(source, sink);
		if (res == sum) puts("possible");
		else puts("impossible");
	}
	return 0;
}

