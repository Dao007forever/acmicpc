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

#define th(x) this->x = x
const int MAXN = 20000 + 10;
const int MAXM = 200000 + 10;
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
		bool vis[MAXN];
		int ret;
		void dfs(int u) {
			vis[u] = true;
			for (int i = E[u]; i != -1; i = buf[i].next) {
				if (!vis[buf[i].b]) {
					if (u < n / 2 && buf[i].cap - buf[i].flow == 0) ret++;
					dfs(buf[i].b);
				}
			}
		}
		void output() {
			ret = 0;
			memset(vis, 0, sizeof(vis));
			dfs(source);
			printf("%d\n", ret);
		}
}sap;
int n, m, S, T;

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &m) != EOF) {
		sap.init(2 * n);
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			sap.addCap(x + n, y, inf);
		}
		scanf("%d%d", &S, &T);
		for (int i = 0; i < n; i++)
			if (i != S && i != T) sap.addCap(i, i + n, 1);
			else sap.addCap(i, i + n, 2);
		T += n;
		if (S + n == T) {
			printf("1\n");
			continue;
		}
		int flow = sap.solve(S, T);
		if (flow == 0) printf("%d\n", n);
		else if (flow == 2) {
			printf("2\n");
		} else {
			sap.output();
		}
	} 
	return 0;
}
