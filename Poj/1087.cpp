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

const int MAXN = 500 + 10;
const int inf = 0x3f3f3f3f;
int T, a, b, c;
char temp1[MAXN], temp2[MAXN];
char dev[MAXN][MAXN], rec[MAXN][MAXN];
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
map<string, int> r;

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &a) != EOF)
	{
		sap.init(0);
		int n = 1, source = 0, sink = 1;
		for (int i = 1; i <= a; i++)
		{
			string t;
			cin >> t;
			r[t] = ++n;
			sap.addCap(n, sink, 1);
			//cout << n << " " << sink << " 1" << endl;
		}
		cin >> b;
		for (int i = 1; i <= b; i++)
		{
			string t1, t2;
			cin >> t1 >>t2;
			r[t1] = ++n;
			sap.addCap(source, n, 1);
			//cout << source << " " << n << " 1" << endl;
			if (!r.count(t2))
				r[t2] = ++n;
			sap.addCap(r[t1], r[t2], 1);
			//cout << r[t1] << " " << r[t2] << " 1" << endl;
		}
		cin >> c;
		for (int i = 1; i <= c; i++)
		{
			string t1, t2;
			cin >> t1 >> t2;
			if (!r.count(t1))
				r[t1] = ++n;
			if (!r.count(t2))
				r[t2] = ++n;
			sap.addCap(r[t1], r[t2], inf);
			//cout << r[t1] << " " << r[t2] << " " << inf << endl;
		}
		sap.n = ++n;
		//cout << sap.n << endl;
		//cout << sap.solve(source, sink) << endl;
		int res = sap.solve(source, sink);
		cout << b - res << endl;
	}
	return 0;
}
