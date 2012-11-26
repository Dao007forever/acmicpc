/*
 * Author:  Yang Zhang
 * Created Time:  2012年08月02日 星期四 20时40分57秒
 * File Name: main.cpp
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
const int MAXN = 1000 + 10;
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

int n, m, tot;
int person[MAXN], u[MAXN], v[MAXN], w[MAXN], p[MAXN];

void solve() {
    int ret = 0, cost = 0;
    int source = 0, sink = n + 1;
    for (int st = 0; st < (1 << tot); st++) {
        sap.init(n + 2);

        //build graph
        int tmp = 0, j = 0;
        for (int i = 1; i <= n; i++) {
            sap.addCap(source, i, person[i]);
        }
        for (int i = 1; i <= m; i++) {
            if (p[i] < 0) {
                sap.addCap(u[i], sink, w[i]);
                sap.addCap(u[i], v[i], inf);
            }
            if (p[i] == 0) {
                sap.addCap(u[i], v[i], inf);
            } 
            if (p[i] > 0) {
                if (st & (1 << j)) {
                    sap.addCap(u[i], v[i], inf);
                    tmp += w[i];
                } else {
                    sap.addCap(u[i], v[i], 1);
                }
                j++;
            }
        }
        int ans = sap.solve(source, sink);
        if (ans > ret || (ans == ret && tmp < cost)) {
            ret = ans; cost = tmp;
        }
    }
    if (ret == 0) puts("Poor Heaven Empire");
    else printf("%d %d\n", ret, cost);
}

int main() {
    freopen("in.txt", "r", stdin);
    while (~scanf("%d%d", &n, &m)) {
        bool flag = false;
        tot = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &person[i]);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d%d%d", &u[i], &v[i], &w[i], &p[i]);
            if (p[i] > 0) tot++;
            if (p[i] < 0) {
                flag = true;
            }
        }
        if (!flag) {
            puts("Poor Heaven Empire");
            continue;
        }
        solve();
    }
    return 0;
}
