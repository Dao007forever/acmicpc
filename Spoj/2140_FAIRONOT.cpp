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

const int MAXN = 2000 + 10;
const int inf = 0x3f3f3f3f;
struct SAP
{
    int cap[MAXN][MAXN], flow[MAXN][MAXN], g[MAXN][MAXN];
    int n;
    int h[MAXN], vh[MAXN], source, sink;
    void init(int n)
    {
        this->n = n;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				cap[i][j] = 0;
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
    bool output(int source, int sink, int m)
    {
		for (int i = 1; i < n; i++)
			if (cap[i + m][sink] - flow[i + m][sink] < 0) return false;
		for (int i = 1; i <= m; i++)
			if (cap[source][i] - flow[source][i]) return false;
		 return true;
    }
}sap;
int n, m;
int score[111];

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d", &n) && n != -1)
	{
		memset(score, 0, sizeof(score));
		scanf("%d", &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &score[i]);
		sap.init(n + m + 1);
		int source = 0, sink = n + m;
		for (int i = 1; i <= m; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if (a == n || b == n) score[n] += 2;
			else
			{
				sap.addCap(source, i, 2);
				sap.addCap(i, a + m, 2);
				sap.addCap(i, b + m, 2);
			}
		}
		for (int i = 1; i < n; i++)
			sap.addCap(i + m, sink, score[n] - score[i] - 1);
		sap.solve(source, sink);
		if (sap.output(source, sink, m)) puts("YES");
		else puts("NO");
	}
	return 0;
}
