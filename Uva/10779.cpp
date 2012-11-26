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
	void test()
	{
		for (int i = 0; i < n; i++)
			if (flow[i][15] > 0)
			{
				printf("%d!!!!!\n", i);
			}
	}
}sap;

int n, m;
int num[15][55], source[15], sink[15];

int ID(int i, int j)
{
	return (i - 1) * m + j;
}

void build()
{
	for (int i = 1; i <= n; i++)
	{
		if (i > 1) 
		{
			sap.addCap(sink[i], source[i], inf);
			//cout << sink[i] << " " << source[i] << " inf" << endl;
		}
		for (int j = 1; j <= m; j++)
		{
			if (num[i][j] == 0)
			{
				sap.addCap(ID(i, j), sink[i], 1);
				//cout << ID(i, j) << " " << sink[i] << " 1" << endl;
			}
			if (num[i][j] > 1) 
			{
				sap.addCap(source[i], ID(i, j), num[i][j] - 1);
				//cout << source[i] << " " << ID(i, j) << " " << num[i][j] << endl;
			}
		}
	}
	for (int k = 1; k <= m; k++)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			if (i != j)
			{
				if (num[i][k] > 1 && num[j][k] == 0) 
				{
					sap.addCap(ID(i, k), ID(j, k), num[i][k] - 1);
					//cout << ID(i, k) << " " << ID(j, k) << " " << num[i][k] - 1 << endl;
				}
			}
	}
}
int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++)
	{
		memset(num, 0, sizeof(num));
		memset(source, 0, sizeof(source));
		memset(sink, 0, sizeof(sink));
		printf("Case #%d: ", cas);
		scanf("%d%d", &n, &m);
		sap.init(n * m + 2 * n);
		source[1] = 0, sink[1] = n * m + 2 * n - 1;
		int now = n * m + 1;
		for (int i = 2; i <= n; i++)
		{
			source[i] = now++;
			sink[i] = now++; 
		}
		for (int i = 1; i <= n; i++)
		{
			int len;
			scanf("%d", &len);
			for (int j = 1; j <= len; j++)
			{
				int k;
				scanf("%d", &k);
				num[i][k]++;
			}
		}
		build();
		int ans = 0;
		for (int i = 1; i <= m; i++)
			if (num[1][i] >= 1) ans++;
		int res = sap.solve(source[1], sink[1]);
		//sap.test();
		printf("%d\n", ans + res);
	}
	return 0;
}
