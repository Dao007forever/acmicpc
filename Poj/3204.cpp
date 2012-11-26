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
const int MAXM = 20000 + 10;
const int inf = 0x3f3f3f3f;
struct Nod
{
        int a, b, next;
        int cap, flow;
        void init(int a, int b, int cap, int next)
        {
				th(a);
                th(b);
                th(cap);
                th(next);
        }
};
struct SAP
{
        int E[MAXN], n;
        int h[MAXN], vh[MAXN], source, sink;
		int vis1[MAXN], vis2[MAXN];
        Nod buf[MAXM * 4]; int len;
        void init(int n)
        {
                this->n = n;
                len = 0;
                memset(E, 255, sizeof(E));
				memset(vis1, 0, sizeof(vis1));
				memset(vis2, 0, sizeof(vis2));
        }
        void addCap(int i, int j, int cap1, int cap2 = 0)
        {
                buf[len].init(i, j, cap1, E[i]);
                E[i] = len++;
                buf[len].init(j, i, cap2, E[j]);
                E[j] = len++;
        }
        int sap(const int idx, const int maxCap)
        {
                if (idx == sink)
                        return maxCap;
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

		void dfs1(int u)
		{
			vis1[u] = true;
			for (int i = E[u]; i != -1; i = buf[i].next)
			{
				int v = buf[i].b;
				if (buf[i].cap - buf[i].flow > 0 && !vis1[v])
					dfs1(v);
			}
		}

		void dfs2(int u)
		{
			vis2[u] = true;
			for (int i = E[u]; i != -1; i = buf[i].next)
			{
				int v = buf[i].b;
				if (buf[i ^ 1].cap - buf[i ^ 1].flow > 0 && !vis2[v])
					dfs2(v);
			}
		}

		void output()
		{
			int cnt = 0;
			for (int i = 0; i < len; i += 2)
			{
				int a = buf[i].a, b = buf[i].b;
				if (buf[i].cap - buf[i].flow == 0 && vis1[a] && vis2[b])
					cnt++;
			}
			printf("%d\n", cnt);
		}
};

SAP sap;
int N, M;

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		int source = 0, sink = N - 1;
		sap.init(N);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			sap.addCap(u, v, w);
		}
		int tmp = sap.solve(source, sink);
		sap.dfs1(source);
		sap.dfs2(sink);
		sap.output();
	}
	return 0;
}
