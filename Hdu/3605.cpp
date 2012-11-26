/*
 * Author : Yang Zhang
 */
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;
/*------------#include omitted-----------*/
#define th(x) this->x = x
const int MAXN = 1310 + 10;
const int MAXM = 20000 + 10;
const int inf = 0x3f3f3f3f;
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
			//cout << i << " " << j << " " << cap1 << endl;
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
}sap;

int cnt[1300];
int main() {
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		memset(cnt, 0, sizeof(cnt));
		sap.init((1 << m) + m + 2);
		int source = (1 << m) + m, sink = (1 << m) + m + 1;
		for (int i = 1; i <= n; i++) {
			int state = 0;
			for (int j = 0; j < m; j++) {
				int x;
				scanf("%d", &x);
				if (x) state |= (1 << j);
			}
			cnt[state]++;
		}
		for (int i = 0; i < (1 << m); i++) {
			if (cnt[i] == 0) continue;
			sap.addCap(source, i, cnt[i]);
			for (int j = 0; j < m; j++)
				if (i & (1 << j)) {
					sap.addCap(i, (1 << m) + j, cnt[i]);
				}
		}
		for (int j = 0; j < m; j++) {
			int x;
			scanf("%d", &x);
			sap.addCap((1 << m) + j, sink, x);
		}
		int ret = sap.solve(source, sink);
		if (ret == n) puts("YES");
		else puts("NO");
	}
	return 0;
}
