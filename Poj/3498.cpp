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

#define MAXN 200 + 10
const int inf = 0x3f3f3f3f;
const double eps = 1e-6;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

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
int N, tot;
double D;
int X[MAXN], Y[MAXN], res[MAXN];

double dist(int i, int j)
{
	return sqrt((X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]));
}

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%lf", &N, &D);
		int source = 0, sink = 2 * N + 1, sum = 0;
		sap.init(2 * N + 2);
		for (int i = 1; i <= N; i++)
		{
			int n, m;
			scanf("%d%d%d%d", &X[i], &Y[i], &n, &m);
			sum += n;
			sap.addCap(source, i, n);
			sap.addCap(i, i + N, m);
			//cout << "source " << i << " " << n << endl;
			//cout << i << " " << i + N << " " << m << endl;
		}
		for (int i = 1; i <= N; i++)
			for (int j = i + 1; j <= N; j++)
				if (dblcmp(dist(i, j) - D) <= 0)
				{
					sap.addCap(i + N, j, inf);
					sap.addCap(j + N, i, inf);
					//cout << i + N << " " << j << " " << inf << endl;
					//cout << j + N << " " << i << " " << inf << endl;
				}
		tot = 0;
		/*for (int i = 1; i <= N; i++)
		{
			if (sap.solve(source, i) == sum)
			{
				res[tot++] = i;
			}
		}*/
		for (int i = 1; i <= N; i++)
		{
			int temp = sap.cap[i][i + N];
			sap.cap[i][i + N] = inf;
			sap.cap[i + N][sink] = inf;
			int maxflow = sap.solve(source, sink);
			if (maxflow == sum) res[tot++] = i;
			sap.cap[i][i + N] = temp;
			sap.cap[i + N][sink] = 0;
		}
		if (tot == 0)
			cout << -1 << endl;
		else
		{
			for (int i = 0; i < tot; i++)
				cout << res[i] - 1 << " ";
			cout << endl;
		}
	}
	return 0;
}
