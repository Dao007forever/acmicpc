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
}sap;

int N, M;
int cap[MAXN];

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) != EOF)
	{
		int source = 0, sink = 2 * N + 1;
		sap.init(2 * N + 2);
		for (int i = 1; i <= N; i++)
			scanf("%d", &cap[i]);
		for (int i = 1; i <= N; i++)
		{
			sap.addCap(i, i + N, cap[i]);
			//cout << i << " " << i + N << " " << cap[i] << endl;
		}
		scanf("%d", &M);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			sap.addCap(u + N, v, w);
			//cout << u + N << " " << v << " " << w << endl;
		}
		int B, D;
		scanf("%d%d", &B, &D);
		for (int i = 1; i <= B; i++)
		{
			int x;
			scanf("%d", &x);
			sap.addCap(source, x, inf);
			//cout << source << " " << x << " inf" << endl;
		}
		for (int i = 1; i <= D; i++)
		{
			int x;
			scanf("%d", &x);
			sap.addCap(x + N, sink, inf);
			//cout << x + N << " " << sink << " inf" << endl;
		}
		int res = sap.solve(source, sink);
		cout << res << endl;
	}
	return 0;
}
