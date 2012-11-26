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

const int MAXN = 150 + 10;
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
	void dfs(int u)//dfs找出从S开始的割集，mk[i]=1表示与S在同一个割集中
    {
        mk[u] = 1;
        for (int i = 0; i < n; i++)
        {
            if (!mk[i] && cap[u][i] - flow[u][i] > 0) dfs(i);
        }
    }

	void resetCap()
	{
		memset(mk, 0, sizeof(mk));
		/*for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (cap[i][j] - flow[i][j] == 0)
					cap[i][j] = 0;*/
		memset(flow, 0, sizeof(flow));
	}
}sap;

int n, m, q;
int mincut[MAXN][MAXN];

void init()
{
	scanf("%d%d", &n, &m);
	sap.init(n);
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--; v--;
		sap.addCap(u, v, w);
		sap.addCap(v, u, w);
	}
}

void solve(vector<int> cur)
{
	if (cur.size() <= 1) return;
	int s = cur[0], t = cur[1];
	sap.resetCap();
	int cut = sap.solve(s, t);
	sap.dfs(s);
	for (int i = 0; i < n; i++)
		if (sap.mk[i])
			for (int j = 0; j < n; j++)
				if (!sap.mk[j])
					mincut[i][j] = mincut[j][i] = min(mincut[i][j], cut);
	vector<int> ch[2];
	for (int i = 0; i < cur.size(); i++)
	{
		if (sap.mk[cur[i]]) ch[0].push_back(cur[i]);
		else ch[1].push_back(cur[i]);
	}
	solve(ch[0]);
	solve(ch[1]);
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		init();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				mincut[i][j] = inf;
		vector<int> cur;
		for (int i = 0; i < n; i++)
			cur.push_back(i);
		solve(cur);
		scanf("%d", &q);
		for (int i = 0; i < q; i++)
		{
			int x;
			scanf("%d", &x);
			int ans = 0;
			for (int i = 0; i < n; i++)
				for (int j = i + 1; j < n; j++)
					if (mincut[i][j] <= x) ans++;
			printf("%d\n", ans);
		}
		if (Test) printf("\n");
	}
	return 0;
}
