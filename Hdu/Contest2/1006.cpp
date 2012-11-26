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
const int M = 1000007;
const int MAXN = 1000 + 10;
const int MAXM = 200000 + 10;
const int inf = 0x3f3f3f3f;
struct Nod
{
        int b, next;
        long long cap, flow;
        void init(int b, long long cap, int next)
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
        void addCap(int i, int j, long long cap1, long long cap2 = 0)
        {
                buf[len].init(j, cap1, E[i]);
                E[i] = len++;
                buf[len].init(i, cap2, E[j]);
                E[j] = len++;
        }
        long long sap(const int idx, const long long maxCap)
        {
                if (idx == sink)
                        return maxCap;
                long long l = maxCap, d;
				int minH = n;
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
        long long solve(int source, int sink)
        {
                if (source == sink) return inf;
                th(source); th(sink);
                memset(h, 0, sizeof(h));
                memset(vh, 0, sizeof(vh));
                for (int i = 0; i < len; i++)
                        buf[i].flow = 0;
				long long ans = 0;
                while (h[source] != n)
                        ans += sap(source, inf);
                return ans;
        }
}sap;

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++)
	{
		printf("Case %d: ", cas);
		int n, m;
		scanf("%d%d", &n, &m);
		sap.init(n);
		for (int i = 1; i <= m; i++)
		{
			int u, v, c, d;
			scanf("%d%d%d%d", &u, &v, &c, &d);
			if (d == 0)
			{
				sap.addCap(u, v, (long long)c * M + 1);
				//cout << u << " " << v << " " << c << " 1" << endl;
			}
			else 
			{
				sap.addCap(u, v, (long long)c * M + 1);
				sap.addCap(v, u, (long long)c * M + 1);
				//cout << u << " " << v << " " << c << " 1" << endl;
				//cout << v << " " << u << " " << c << " 1" << endl;
			}
		}
		long long ans = sap.solve(0, n - 1);
		ans %= M;
		cout << ans << endl;
	}
	return 0;
}
