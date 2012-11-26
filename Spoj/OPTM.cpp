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

const int MAXN = 500 + 10;
const int MAXM = 3000 + 10;
const int inf = 0x3f3f3f3f;
int T, N, M, K;
int mark[MAXN], cnt[MAXN], u[MAXM], v[MAXM], vis[MAXN];
struct Nod
{
	int b, next;
	int cap, flow;
	void init(int b, int cap, int next)
	{
		th(b); th(cap); th(next);
	}
};
struct SAP
{
	int E[MAXN], n;
	int h[MAXN], vh[MAXN], source, sink;
	Nod buf[4 * MAXM]; int len;
	void init(int n)
    {
		this->n = n;
		len = 0;
        memset(E, 255, sizeof(E));
    }
    void addCap(int i, int j, int cap1, int cap2 = 0)
    {
		buf[len].init(j, cap1, E[i]);
        E[i] = len++;
        buf[len].init(i, cap2, E[j]);
        E[j] = len++;
    }
    int sap(const int idx, const int maxCap)
    {
		if (idx == sink) return maxCap;
        int l = maxCap, d, minH = n;
        for (int i = E[idx]; i != -1; i = buf[i].next)
        {
			Nod & nod = buf[i];
            if (nod.cap-nod.flow > 0)
            {
				if (h[idx] == h[nod.b] + 1)
                {
					d = sap(nod.b, min(l, nod.cap - nod.flow));
                    nod.flow += d;
                    buf[i ^ 1].flow -= d;
                    l -= d;
                    if (h[source] == n || l == 0) return maxCap - l;
                }
                minH = min(minH, h[nod.b] + 1);
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
        th(source); th(sink);
        memset(h, 0, sizeof(h));
        memset(vh, 0, sizeof(vh));
        for (int i = 0; i < len; i++)
			buf[i].flow = 0;
		int ans = 0;
        while (h[source] != n)
			ans += sap(source, inf);
		return ans;
    }
	void dfs(int u, int base)
	{
		cnt[u] += base;
		vis[u] = 1;
		for (int i = E[u]; i != -1; i = buf[i].next)
		{
			if (buf[i].cap - buf[i].flow > 0 && !vis[buf[i].b])
				dfs(buf[i].b, base);
		}
	}
};

SAP sap;

void Solve()
{
	int flag, base, i;
	flag = 1;
	base = 1;
	memset(cnt, 0, sizeof(cnt));
	while (flag)
	{
		flag = 0;
		sap.init(N + 2);
		int source = 0, sink = N + 1;
		for (int i = 0; i < M; i++)
		{
			sap.addCap(u[i], v[i], 1, 1);
		}
		for (int i = 1; i <= N; i++)
		{
			if (mark[i] != -1)
			{
				if (mark[i] >= 1)
					flag = 1;
				if (mark[i] % 2)
				{
					sap.addCap(source, i, inf, 0);
				}
				else
				{
					sap.addCap(i, sink, inf, 0);
				}
				mark[i] /= 2;
			}
		}
		sap.solve(source, sink);
		memset(vis, 0, sizeof(vis));
		sap.dfs(source, base);
		base *= 2;
	}
	for (int i = 1; i <= N; i++)
		cout << cnt[i] << endl;
}

int main()
{
	freopen("a", "r", stdin);
	cin >> T;
	while (T--)
	{
		cin >> N >> M;
		for (int i = 0; i < M; i++)
			cin >> u[i] >> v[i];
		cin >> K;
		memset(mark, -1, sizeof(mark));
		for (int i = 0; i < K; i++)
		{
			int x, p;
			cin >> x >> p;
			mark[x] = p;
		}
		Solve();
	}
	return 0;
}
