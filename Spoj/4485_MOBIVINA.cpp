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

const int MAX = 11;
const int MAXN = 300 + 10;
const int inf = 0x3f3f3f3f;
struct SAP
{
    int cap[MAXN][MAXN], flow[MAXN][MAXN], g[MAXN][MAXN];
    int n;
    int h[MAXN], vh[MAXN], source, sink;
    int mk[MAXN];
    void init(int n)
    {
        this->n = n;
        memset(cap, 0, sizeof(cap));
        memset(g, 0, sizeof(g));
        memset(mk, 0, sizeof(mk));
    }
    void addCap(int i, int j, int val)
    {
        cap[i][j] += val;
        g[i][j] = 1;
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
int n;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	int source = 0, sink = n + 1;
	sap.init(n + 2);
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		sap.addCap(source, i, x);
	}
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		sap.addCap(i, sink, x);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			int x;
			scanf("%d", &x);
			sap.addCap(i, j, x);
		}
	int ans = sap.solve(source, sink);
	cout << ans << endl;
	return 0;
}
