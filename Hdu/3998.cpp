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
 
const int MAXN = 10000 + 10;
const int MAXM = 1000000 + 10;
const int inf = 0x3f3f3f3f;
int N, len;
int a[MAXN], f[MAXN];
 
struct Nod
{
        int b, next;
        int cap, flow;
        void init(int b, int cap, int next)
        {
                th(b);
                th(cap);
                th(next);
        }
};
struct SAP
{
        int E[MAXN], n;
        int h[MAXN], vh[MAXN], source, sink;
        Nod buf[MAXM * 4]; int len;
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
};
 
SAP sap;
 
int solve1()
{
	int ans = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j < i; j++)
			if (a[j] < a[i] && f[j] + 1 > f[i])
			{
				f[i] = f[j] + 1;
				ans = max(f[i], ans);
			}
	return ans;
}
 
void solve2()
{
	int source = 0, sink = N + 1;
	sap.init(N + 2);
	for (int i = 1; i <= N; i++)
	{
		if (f[i] == 1) sap.addCap(source, i, 1);
		if (f[i] == len) sap.addCap(i, sink, 1);
	}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j < i; j++)
			if (a[j] < a[i] && f[j] + 1 == f[i])
				sap.addCap(j, i, 1);
	cout << sap.solve(source, sink) << endl;
}
 
int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) != EOF)
	{
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &a[i]);
			f[i] = 1;
		}
		len = solve1();
		printf("%d\n", len);
		solve2();
	}
	return 0;
}
