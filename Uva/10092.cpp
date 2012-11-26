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
const int MAXN = 2222;
const int inf = 0x3f3f3f3f;
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
int n, m;
int ans[1111];

void dfs()
{
	for (int i = 1; i <= n; i++)
	{
		int t = 0;
		for (int j = n + 1; j <= n + m; j++)
			if (sap.cap[i][j] != 0 && sap.cap[i][j] - sap.flow[i][j] == 0)
				ans[++t] = j - n;
		for (int j = 1; j <= t; j++)
		{
			if (j == t) printf("%d\n", ans[j]);
			else printf("%d ", ans[j]);
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &n, &m))
	{
		if (n == 0 && m == 0) break;
		int sum = 0, source = 0, sink = n + m + 1;
		sap.init(n + m + 2);
		for (int i = 1; i <= n; i++)
		{
			int x;
			scanf("%d", &x);
			sum += x;
			sap.addCap(source, i, x);
		}
		for (int i = 1; i <= m; i++)
		{
			int num;
			scanf("%d", &num);
			for (int j = 1; j <= num; j++)
			{
				int x;
				scanf("%d", &x);
				sap.addCap(x, i + n, 1);
			}
			sap.addCap(i + n, sink, 1);
		}
		int tmp = sap.solve(source, sink);
		if (tmp == sum)
		{
			printf("1\n");
			dfs();
		}
		else printf("0\n");
	}
	return 0;
}
